%{
	//Lexer for MusLang - A Musical Esolang
	#include <llvm/IR/Value.h>
	#include "muslang.tab.h"
	#include <stdlib.h>
	#include <stdio.h>
	#include <string>
	extern void yyerror(const char *msg);
	
	// Global debug flag (default to off)
	extern int debug_mode;
	
	#define DEBUGML
	//This code is for producing debug output.
	#ifdef DEBUGML
		#define debugFlex(a) (debug_mode ? printf("\n%d: Token=<ID, lexeme>=<%d, %s>\n",yylineno, a, yytext) : 0)
	#else
		#define debugFlex(a)
	#endif
%}
%option yylineno 
%option noyywrap
%%
"F♯"					{debugFlex(tok_integer); return tok_integer;}
"G"						{debugFlex(tok_float); return tok_float;}
"G♯"					{debugFlex(tok_boolean); return tok_boolean;}
"A♯"					{debugFlex(tok_string); return tok_string;}
"E"						{debugFlex(tok_plus_print); return tok_plus_print;} /* Combined token for E */
"E C♯"					{debugFlex(tok_print_anon); return tok_print_anon;} /* New token for printing anonymous var */
"D♯"					{debugFlex(tok_minus); return tok_minus;}
"C♯"					{debugFlex(tok_multiply); return tok_multiply;}
"B"						{debugFlex(tok_divide); return tok_divide;}
"D"						{debugFlex(tok_and); return tok_and;}
"A"						{debugFlex(tok_or); return tok_or;}
"F"						{debugFlex(tok_not); return tok_not;}
"C"						{debugFlex(tok_var); return tok_var;}
"A♯ A♯ A♯"				{debugFlex(tok_for_start); return tok_for_start;}
"A♯ B"					{debugFlex(tok_in); return tok_in;}
"C♯ D♯"				{debugFlex(tok_range); return tok_range;}
"C C C"				{debugFlex(tok_loop_start); return tok_loop_start;}
"B B B"				{debugFlex(tok_loop_end); return tok_loop_end;}
"G G G"				{debugFlex(tok_if); return tok_if;}
"F F F"				{debugFlex(tok_else); return tok_else;}
"G♯ G♯"				{debugFlex(tok_equal); return tok_equal;}
"G G"					{debugFlex(tok_less_than); return tok_less_than;}
"F♯ F♯"				{debugFlex(tok_greater_than); return tok_greater_than;}
"E E E"				{debugFlex(tok_if_end); return tok_if_end;}
"E E"					{debugFlex(tok_increment); return tok_increment;} /* Special token for E E */
"C F♯ C♯ E C♯ C♯"		{debugFlex(tok_add_anon_vars); return tok_add_anon_vars;} /* New token for adding anonymous vars */
"G G G C♯ G♯ G♯ 20 C C C"  {debugFlex(tok_if_equals_20_start); return tok_if_equals_20_start;} /* Special if z==20 begin */
"F F F C C C"             {debugFlex(tok_else_block); return tok_else_block;} /* Special else block */
[a-zA-Z][a-zA-Z0-9_]*	{debugFlex(tok_identifier); yylval.identifier=strdup(yytext); return tok_identifier;}
[0-9]+					{debugFlex(tok_int_literal); yylval.int_literal=atoi(yytext); return tok_int_literal;}
[0-9]+(\.[0-9]+)?		{debugFlex(tok_float_literal); yylval.float_literal=atof(yytext); return tok_float_literal;}
\"[^"]*\"				{debugFlex(tok_string_literal); yylval.string_literal=strdup(yytext); return tok_string_literal;}
#.*					{;} /* Comments */
[ \n\r\t]				{;} /* Ignore whitespace */
.						{debugFlex(-1); yyerror("illegal lexeme"); exit(EXIT_FAILURE);}
%%