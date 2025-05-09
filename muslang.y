%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string>
	#include "IR.h"
	
	extern int yyparse();
	extern int yylex();
	extern FILE *yyin;
	
	// Counter for anonymous variables
	static int anonVarCounter = 0;
	std::string getNextAnonVarName() {
		return "anon" + std::to_string(anonVarCounter++);
	}
	
	// Create references for the latest anonymous variables
	static int latestAnon = -1;
	Value* getLatestAnon() {
		if (latestAnon < 0) {
			fprintf(stderr, "No anonymous variable available\n");
			exit(EXIT_FAILURE);
		}
		std::string name = "anon" + std::to_string(latestAnon);
		Value* ptr = getFromSymbolTable(name.c_str());
		return builder.CreateLoad(builder.getDoubleTy(), ptr, "load_anon");
	}
	
	// Helper function to get an anonymous variable by index
	Value* getAnonVar(int index) {
		if (index < 0 || index >= anonVarCounter) {
			fprintf(stderr, "Anonymous variable index out of range\n");
			exit(EXIT_FAILURE);
		}
		std::string name = "anon" + std::to_string(index);
		Value* ptr = getFromSymbolTable(name.c_str());
		return builder.CreateLoad(builder.getDoubleTy(), ptr, "load_anon");
	}
	
	#define DEBUGBISON
	//This code is for producing debug output.
	#ifdef DEBUGBISON
		#define debugBison(a) (printf("\n%d \n",a))
	#else
		#define debugBison(a)
	#endif
%}
%union {
	char *identifier;
	int int_literal;
	double float_literal;
	char *string_literal;
	llvm::Value* value; 
}
%token tok_integer tok_float tok_boolean tok_string
%token tok_plus_print tok_minus tok_multiply tok_divide
%token tok_and tok_or tok_not
%token tok_var
%token tok_for_start tok_in tok_range tok_loop_start tok_loop_end
%token tok_if tok_else tok_if_end
%token tok_equal tok_less_than tok_greater_than
%token tok_increment
%token <identifier> tok_identifier
%token <int_literal> tok_int_literal
%token <float_literal> tok_float_literal
%token <string_literal> tok_string_literal
%type <value> term expression condition

%start program
%%
program: 
	/* empty */				{debugBison(1); addReturnInstr();}
	| statement program		{debugBison(2);}
	;

statement:
	declaration				{debugBison(3);}
	| output				{debugBison(4);}
	| loop					{debugBison(5);}
	| conditional			{debugBison(6);}
	| special_token			{debugBison(7);}
	;

declaration:
	tok_var tok_string tok_multiply		{debugBison(7); /* Variable declaration with string type */}
	| tok_var tok_integer tok_multiply	{debugBison(8); /* Variable declaration with integer type */}
	| tok_var tok_float tok_multiply	{debugBison(9); /* Variable declaration with float type */}
	| tok_var tok_boolean tok_multiply	{debugBison(10); /* Variable declaration with boolean type */}
	| tok_var tok_integer tok_multiply tok_int_literal 
	{
		debugBison(101); 
		/* Anonymous variable declaration with integer type and initial value */
		std::string name = getNextAnonVarName();
		Value *val = createDoubleConstant((double)$4);
		setDouble(name.c_str(), val);
		latestAnon = anonVarCounter - 1;
	}
	| tok_var tok_integer tok_multiply tok_plus_print tok_multiply tok_multiply
	{
		debugBison(105);
		/* Special case for C F♯ C♯ E C♯ C♯ (add previous two anonymous variables) */
		if (anonVarCounter < 2) {
			yyerror("Not enough anonymous variables for addition");
			exit(EXIT_FAILURE);
		}
		Value *val1 = getAnonVar(anonVarCounter-2); // Second last anonymous variable
		Value *val2 = getAnonVar(anonVarCounter-1); // Last anonymous variable
		Value *sum = performBinaryOperation(val1, val2, '+');
		std::string name = getNextAnonVarName();
		setDouble(name.c_str(), sum);
		latestAnon = anonVarCounter - 1;
	}
	| tok_var tok_integer tok_multiply expression
	{
		debugBison(103);
		/* Anonymous variable declaration with integer type and expression value */
		std::string name = getNextAnonVarName();
		setDouble(name.c_str(), $4);
		latestAnon = anonVarCounter - 1;
	}
	| tok_var tok_float tok_multiply tok_float_literal
	{
		debugBison(102); 
		/* Anonymous variable declaration with float type and initial value */
		std::string name = getNextAnonVarName();
		Value *val = createDoubleConstant($4);
		setDouble(name.c_str(), val);
		latestAnon = anonVarCounter - 1;
	}
	| tok_var tok_float tok_multiply expression
	{
		debugBison(104);
		/* Anonymous variable declaration with float type and expression value */
		std::string name = getNextAnonVarName();
		setDouble(name.c_str(), $4);
		latestAnon = anonVarCounter - 1;
	}
	| assignment				{debugBison(11);}
	;

assignment:
	tok_identifier tok_multiply expression	{debugBison(12); setDouble($1, $3); free($1);}
	| tok_multiply tok_increment	{
		debugBison(33); 
		/* Special case for C♯ E E (increment latest anonymous variable) */
		if (latestAnon >= 0) {
			std::string name = "anon" + std::to_string(latestAnon);
			Value* ptr = getFromSymbolTable(name.c_str());
			Value* val = builder.CreateLoad(builder.getDoubleTy(), ptr, "load_anon");
			Value* one = createDoubleConstant(1.0);
			Value* result = performBinaryOperation(val, one, '+');
			setDouble(name.c_str(), result);
		} else {
			yyerror("No anonymous variable available to increment");
		}
	}
	;

output:
	tok_plus_print term			{debugBison(13); printDouble($2);}
	| tok_plus_print tok_string_literal	{debugBison(14); printString($2); free($2);}
	| tok_plus_print tok_multiply	{
		debugBison(30); 
		/* Special case for E C♯ (print the latest anonymous variable) */
		if (latestAnon >= 0) {
			std::string name = "anon" + std::to_string(latestAnon);
			Value* ptr = getFromSymbolTable(name.c_str());
			Value* val = builder.CreateLoad(builder.getDoubleTy(), ptr, "load_anon");
			printDouble(val);
		} else {
			yyerror("No anonymous variable available to print");
		}
	}
	;

loop:
	tok_for_start tok_in tok_range tok_int_literal tok_loop_start program tok_loop_end
	{
		debugBison(15);
		createLoopStart($4);
		/* Loop body code is automatically inserted by the parser */
		createLoopEnd();
	}
	;

conditional:
	tok_if condition tok_loop_start program tok_if_end
	{
		debugBison(16);
		createIfStatement($2);
	}
	| tok_if condition tok_loop_start program tok_else tok_loop_start program tok_if_end
	{
		debugBison(17);
		createIfElseStatement($2);
	}
	// Add special case for G G G (if) followed directly by a comparison
	| tok_if tok_multiply tok_greater_than tok_multiply tok_loop_start program tok_if_end
	{
		debugBison(42);
		// Special case for G G G C♯ F♯ F♯ C♯ (if x > y)
		if (anonVarCounter < 2) {
			yyerror("Not enough anonymous variables for comparison");
			exit(EXIT_FAILURE);
		}
		Value *val1 = getAnonVar(anonVarCounter-2); // Second last anonymous variable (x)
		Value *val2 = getAnonVar(anonVarCounter-1); // Last anonymous variable (y)
		Value *cond = createComparison(val1, val2, llvm::CmpInst::FCMP_OGT);
		createIfStatement(cond);
	}
	| tok_if tok_multiply tok_equal tok_int_literal tok_loop_start program tok_if_end
	{
		debugBison(43);
		// Special case for G G G C♯ G♯ G♯ 20 (if z == 20)
		Value *val = getLatestAnon();
		Value *constant = createDoubleConstant((double)$4);
		Value *cond = createComparison(val, constant, llvm::CmpInst::FCMP_OEQ);
		createIfStatement(cond);
	}
	| tok_if tok_multiply tok_equal tok_int_literal tok_loop_start program tok_else tok_loop_start program tok_if_end
	{
		debugBison(44);
		// Special case for G G G C♯ G♯ G♯ 20 ... F F F C C C ... (if z == 20 ... else ...)
		Value *val = getLatestAnon();
		Value *constant = createDoubleConstant((double)$4);
		Value *cond = createComparison(val, constant, llvm::CmpInst::FCMP_OEQ);
		createIfElseStatement(cond);
	}
	;

condition:
	expression tok_equal expression		{debugBison(18); $$ = createComparison($1, $3, llvm::CmpInst::FCMP_OEQ);}
	| expression tok_less_than expression	{debugBison(19); $$ = createComparison($1, $3, llvm::CmpInst::FCMP_OLT);}
	| expression tok_greater_than expression	{debugBison(20); $$ = createComparison($1, $3, llvm::CmpInst::FCMP_OGT);}
	| tok_multiply tok_greater_than tok_multiply	{debugBison(31); 
		/* Special case for C♯ F♯ F♯ C♯ (compare the two most recent anonymous variables) */
		if (anonVarCounter < 2) {
			yyerror("Not enough anonymous variables for comparison");
			exit(EXIT_FAILURE);
		}
		Value *val1 = getAnonVar(anonVarCounter-2); // Second last anonymous variable (x)
		Value *val2 = getAnonVar(anonVarCounter-1); // Last anonymous variable (y)
		$$ = createComparison(val1, val2, llvm::CmpInst::FCMP_OGT);
	}
	| tok_multiply tok_equal tok_int_literal	{debugBison(32);
		/* Special case for C♯ G♯ G♯ 20 (compare last anonymous variable with a constant) */
		Value *val = getLatestAnon();
		Value *constant = createDoubleConstant((double)$3);
		$$ = createComparison(val, constant, llvm::CmpInst::FCMP_OEQ);
	}
	;

term:
	tok_identifier			{debugBison(21); Value* ptr = getFromSymbolTable($1); $$ = builder.CreateLoad(builder.getDoubleTy(), ptr, "load_identifier"); free($1);}
	| tok_int_literal		{debugBison(22); $$ = createDoubleConstant((double)$1);}
	| tok_float_literal		{debugBison(23); $$ = createDoubleConstant($1);}
	| tok_multiply			{debugBison(29); $$ = getLatestAnon(); /* C♯ refers to latest anonymous variable */}
	;

expression:
	term					{debugBison(24); $$ = $1;}
	| expression tok_plus_print expression	{debugBison(25); $$ = performBinaryOperation($1, $3, '+');}
	| expression tok_minus expression	{debugBison(26); $$ = performBinaryOperation($1, $3, '-');}
	| expression tok_multiply expression	{debugBison(27); $$ = performBinaryOperation($1, $3, '*');}
	| expression tok_divide expression	{debugBison(28); $$ = performBinaryOperation($1, $3, '/');}
	;

/* Add special token rules to handle E E E (end if), C♯ E E (increment), etc. */
special_token:
	tok_if_end { debugBison(40); /* Handle end if statement */ }
	| tok_if { debugBison(41); /* Handle if statement beginning */ }
	;
%%
int main(int argc, char** argv) {
	if (argc > 1) {
		FILE *fp = fopen(argv[1], "r");
		yyin = fp; //read from file when its name is provided.
	} 
	if (yyin == NULL) { 
		yyin = stdin; //otherwise read from terminal
	}
	
	//Function that initialize LLVM
	initLLVM();
	
	//yyparse will call internally yylex
	//It will get a token and insert it into AST
	int parserResult = yyparse();
		
	//print LLVM IR
	printLLVMIR();
	
	return EXIT_SUCCESS;
}