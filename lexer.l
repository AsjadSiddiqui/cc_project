%{
#include <stdio.h>
#include "parser.tab.h"

/* This is a simple flex lexer for music notation */
%}

%option noyywrap

/* Definitions */
DIGIT       [0-9]
LETTER      [a-zA-Z]
WHITESPACE  [ \t\r\n]

%%

"note"      { return NOTE; }
"rest"      { return REST; }
"tempo"     { return TEMPO; }
"staff"     { return STAFF; }
"key"       { return KEY; }

{DIGIT}+    { yylval.ival = atoi(yytext); return INTEGER; }
{DIGIT}+"."{DIGIT}*  { yylval.fval = atof(yytext); return FLOAT; }

[A-G][#b]?  { yylval.sval = strdup(yytext); return PITCH; }

{WHITESPACE}+ { /* ignore whitespace */ }

.           { printf("Unrecognized character: %s\n", yytext); }

%%

/* Optional user code section */