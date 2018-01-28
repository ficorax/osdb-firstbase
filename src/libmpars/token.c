/*
 * Copyright (C) 2001 FirstBase Software, Inc. All rights reserved.
 *
 * $Id: token.c,v 9.0 2001/01/09 02:56:54 john Exp $
 *
 * See the file LICENSE for conditions of use and distribution.
 *
 */

#include "macro_df.h"
struct tok
{	char *tnm;
	int yval;
} tok[]	= {
"FIRSTTOKEN", 257,
"IF", 258,
"ELSE", 259,
"WHILE", 260,
"FOR", 261,
"BREAK", 262,
"CONTINUE", 263,
"M_RETURN", 264,
"M_EXIT", 265,
"M_LOCAL", 266,
"SWITCH", 267,
"CASE", 268,
"DEFAULT", 269,
"CON", 270,
"FCON", 271,
"CCON", 272,
"SCON", 273,
"OCON", 274,
"ID", 275,
"LSHFT_A", 276,
"RSHFT_A", 277,
"XOR_A", 278,
"AND_A", 279,
"OR_A", 280,
"ADD_A", 281,
"MINUS_A", 282,
"MULT_A", 283,
"DIV_A", 284,
"MOD_A", 285,
"INCR", 286,
"DECR", 287,
"AND", 288,
"EQ", 289,
"NEQ", 290,
"LEQ", 291,
"GEQ", 292,
"OR", 293,
"LSHFT", 294,
"RSHFT", 295,
"M_BEGIN", 296,
"M_BODY", 297,
"M_END", 298,
"M_FUNCTION", 299,
"M_MAIN", 300,
"LOW", 301,
"UNARY", 302,
"LASTTOKEN", 303,
};

ptoken(n)
int n;

{
	if(n<128) printf("lex: %c\n",n);
	else	if(n<=256) printf("lex:? %o\n",n);
	else	if(n<LASTTOKEN) printf("lex: %s\n",tok[n-257].tnm);
	else	printf("lex:? %o\n",n);
	return;
}

char *tokname(n)
int n;

{
	if (n<=256 || n >= LASTTOKEN)
		n = 257;
	return(tok[n-FIRSTTOKEN].tnm);
}
