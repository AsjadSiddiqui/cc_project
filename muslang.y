%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "IR.h"
	
	extern int yyparse();
	extern int yylex();
	extern FILE *yyin;
	
	//#define DEBUGBISON
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
%token tok_plus tok_minus tok_multiply tok_divide
%token tok_and tok_or tok_not
%token tok_var
%token tok_for_start tok_in tok_range tok_loop_start tok_loop_end
%token tok_print
%token <identifier> tok_identifier
%token <int_literal> tok_int_literal
%token <float_literal> tok_float_literal
%token <string_literal> tok_string_literal
%type <value> term expression

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
	;

declaration:
	tok_var tok_string tok_multiply		{debugBison(6); /* Variable declaration with string type */}
	| tok_var tok_integer tok_multiply	{debugBison(7); /* Variable declaration with integer type */}
	| tok_var tok_float tok_multiply	{debugBison(8); /* Variable declaration with float type */}
	| tok_var tok_boolean tok_multiply	{debugBison(9); /* Variable declaration with boolean type */}
	| assignment				{debugBison(10);}
	;

assignment:
	tok_identifier tok_multiply expression	{debugBison(11); setDouble($1, $3); free($1);}
	;

output:
	tok_print term			{debugBison(12); printDouble($2);}
	| tok_print tok_string_literal	{debugBison(13); printString($2); free($2);}
	;

loop:
	tok_for_start tok_in tok_range tok_int_literal tok_loop_start program tok_loop_end
	{
		debugBison(14);
		/* For loop implementation */
	}
	;

term:
	tok_identifier			{debugBison(15); Value* ptr = getFromSymbolTable($1); $$ = builder.CreateLoad(builder.getDoubleTy(), ptr, "load_identifier"); free($1);}
	| tok_int_literal		{debugBison(16); $$ = createDoubleConstant((double)$1);}
	| tok_float_literal		{debugBison(17); $$ = createDoubleConstant($1);}
	;

expression:
	term					{debugBison(18); $$ = $1;}
	| expression tok_plus expression	{debugBison(19); $$ = performBinaryOperation($1, $3, '+');}
	| expression tok_minus expression	{debugBison(20); $$ = performBinaryOperation($1, $3, '-');}
	| expression tok_multiply expression	{debugBison(21); $$ = performBinaryOperation($1, $3, '*');}
	| expression tok_divide expression	{debugBison(22); $$ = performBinaryOperation($1, $3, '/');}
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