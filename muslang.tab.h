/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END = 0,
     tok_integer = 258,
     tok_float = 259,
     tok_boolean = 260,
     tok_string = 261,
     tok_plus_print = 262,
     tok_minus = 263,
     tok_multiply = 264,
     tok_divide = 265,
     tok_and = 266,
     tok_or = 267,
     tok_not = 268,
     tok_var = 269,
     tok_for_start = 270,
     tok_in = 271,
     tok_range = 272,
     tok_loop_start = 273,
     tok_loop_end = 274,
     tok_if = 275,
     tok_else = 276,
     tok_if_end = 277,
     tok_equal = 278,
     tok_less_than = 279,
     tok_greater_than = 280,
     tok_increment = 281,
     tok_print_anon = 282,
     tok_add_anon_vars = 283,
     tok_if_equals_20_start = 284,
     tok_else_block = 285,
     tok_identifier = 286,
     tok_int_literal = 287,
     tok_float_literal = 288,
     tok_string_literal = 289,
     tok_end = 290,
     LOWER_THAN_ELSE = 291
   };
#endif
/* Tokens.  */
#define END 0
#define tok_integer 258
#define tok_float 259
#define tok_boolean 260
#define tok_string 261
#define tok_plus_print 262
#define tok_minus 263
#define tok_multiply 264
#define tok_divide 265
#define tok_and 266
#define tok_or 267
#define tok_not 268
#define tok_var 269
#define tok_for_start 270
#define tok_in 271
#define tok_range 272
#define tok_loop_start 273
#define tok_loop_end 274
#define tok_if 275
#define tok_else 276
#define tok_if_end 277
#define tok_equal 278
#define tok_less_than 279
#define tok_greater_than 280
#define tok_increment 281
#define tok_print_anon 282
#define tok_add_anon_vars 283
#define tok_if_equals_20_start 284
#define tok_else_block 285
#define tok_identifier 286
#define tok_int_literal 287
#define tok_float_literal 288
#define tok_string_literal 289
#define tok_end 290
#define LOWER_THAN_ELSE 291




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 51 "muslang.y"
{
	char *identifier;
	int int_literal;
	double float_literal;
	char *string_literal;
	llvm::Value* value; 
}
/* Line 1529 of yacc.c.  */
#line 131 "muslang.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

