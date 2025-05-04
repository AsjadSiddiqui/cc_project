%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char* s);
extern int yylex();
extern FILE* yyin;

/* This is a simple bison parser for music notation */
%}

%union {
    int ival;
    float fval;
    char* sval;
}

/* Tokens defined in lexer.l */
%token <ival> INTEGER
%token <fval> FLOAT
%token <sval> PITCH
%token NOTE REST TEMPO STAFF KEY

/* Define types for non-terminal symbols */
%type <ival> duration
%type <sval> pitch

%%

program: 
    statement_list
    ;

statement_list:
    statement
    | statement_list statement
    ;

statement:
    note_statement
    | rest_statement
    | tempo_statement
    | staff_statement
    | key_statement
    ;

note_statement:
    NOTE pitch duration {
        printf("Note: %s with duration %d\n", $2, $3);
        free($2);
    }
    ;

rest_statement:
    REST duration {
        printf("Rest with duration %d\n", $2);
    }
    ;

tempo_statement:
    TEMPO INTEGER {
        printf("Set tempo to %d BPM\n", $2);
    }
    ;

staff_statement:
    STAFF INTEGER {
        printf("Set staff to %d lines\n", $2);
    }
    ;

key_statement:
    KEY PITCH {
        printf("Set key to %s\n", $2);
        free($2);
    }
    ;

pitch:
    PITCH { $$ = $1; }
    ;

duration:
    INTEGER { $$ = $1; }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}

#ifdef STANDALONE_PARSER
int main(int argc, char** argv) {
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Could not open file: %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }

    yyparse();
    
    if (argc > 1) {
        fclose(yyin);
    }
    
    return 0;
}
#endif