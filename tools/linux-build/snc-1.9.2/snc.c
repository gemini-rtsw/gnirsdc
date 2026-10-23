#ifndef lint
static char yysccsid[] = "@(#)yaccpar (JRW version from 1.9 (Berkeley) 02/21/93)";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#ifdef __STDC__
static int yyparse(void);
#else
static int yyparse();
#endif
#define YYPREFIX "yy"
#line 2 "../snc.y"
/**************************************************************************
			GTA PROJECT   AT division
	Copyright, 1990, The Regents of the University of California.
		         Los Alamos National Laboratory
	snc.y,v 1.2 1995/06/27 15:26:07 wright Exp
	ENVIRONMENT: UNIX
	HISTORY:
20nov91,ajk	Added new "option" statement.
08nov93,ajk	Implemented additional declarations (see VC_CLASS in parse.h).
08nov93,ajk	Implemented assignment of array elements to pv's.
02may93,ajk	Removed "parameter" definition for functions, and added "%prec"
		qualifications to some "expr" definitions.
31may94,ajk	Changed method for handling global C code.
20jul95,ajk	Added "unsigned" types (see UNSIGNED token).
11jul96,ajk	Added character constants (CHAR_CONST).
***************************************************************************/
/*	SNC - State Notation Compiler.
 *	The general structure of a state program is:
 *		program-name
 *		declarations
 *		ss  { state { event { action ...} new-state } ... } ...
 *
 *	The following yacc definitions call the various parsing routines, which
 *	are coded in the file "parse.c".  Their major action is to build
 *	a structure for each SNL component (state, event, action, etc.) and
 *	build linked lists from these structures.  The linked lists have a
 *	hierarchical structure corresponding to the SNL block structure.
 *	For instance, a "state" structure is linked to a chain of "event",
 *	structures, which are, in turn, linked to a chain of "action"
 *	structures.
 *	The lexical analyser (see snc_lax.l) reads the input
 *	stream and passes tokens to the yacc-generated code.  The snc_lex
 *	and parsing routines may also pass data elements that take on one
 *	of the types defined under the %union definition.
 *
 */
#include	<stdio.h>
#include	<ctype.h>
#include	"parse.h"

#ifndef	TRUE
#define	TRUE	1
#define	FALSE	0
#endif	TRUE

extern	int line_num; /* input file line no. */
#line 52 "../snc.y"
typedef union
{
	int	ival;
	char	*pchar;
	void	*pval;
	Expr	*pexpr;
} YYSTYPE;
#line 72 "y.tab.c"
#define STATE 257
#define STATE_SET 258
#define NUMBER 259
#define NAME 260
#define CHAR_CONST 261
#define DEBUG_PRINT 262
#define PROGRAM 263
#define EXIT 264
#define OPTION 265
#define R_SQ_BRACKET 266
#define L_SQ_BRACKET 267
#define BAD_CHAR 268
#define L_BRACKET 269
#define R_BRACKET 270
#define COLON 271
#define SEMI_COLON 272
#define EQUAL 273
#define L_PAREN 274
#define R_PAREN 275
#define PERIOD 276
#define POINTER 277
#define COMMA 278
#define OR 279
#define AND 280
#define MONITOR 281
#define ASSIGN 282
#define TO 283
#define WHEN 284
#define UNSIGNED 285
#define CHAR 286
#define SHORT 287
#define INT 288
#define LONG 289
#define FLOAT 290
#define DOUBLE 291
#define STRING_DECL 292
#define EVFLAG 293
#define SYNC 294
#define ASTERISK 295
#define AMPERSAND 296
#define AUTO_INCR 297
#define AUTO_DECR 298
#define PLUS 299
#define MINUS 300
#define SLASH 301
#define GT 302
#define GE 303
#define EQ 304
#define LE 305
#define LT 306
#define NE 307
#define NOT 308
#define BIT_OR 309
#define BIT_AND 310
#define L_SHIFT 311
#define R_SHIFT 312
#define COMPLEMENT 313
#define MODULO 314
#define PLUS_EQUAL 315
#define MINUS_EQUAL 316
#define MULT_EQUAL 317
#define DIV_EQUAL 318
#define AND_EQUAL 319
#define OR_EQUAL 320
#define MODULO_EQUAL 321
#define LEFT_EQUAL 322
#define RIGHT_EQUAL 323
#define CMPL_EQUAL 324
#define STRING 325
#define C_STMT 326
#define IF 327
#define ELSE 328
#define WHILE 329
#define FOR 330
#define BREAK 331
#define PP_SYMBOL 332
#define CR 333
#define UOP 334
#define SUBSCRIPT 335
#define YYERRCODE 256
static short yylhs[] = {                                        -1,
    0,    0,    0,    0,    0,   24,   24,   25,   25,   28,
   28,   28,   28,   28,   28,   28,   28,   28,   29,   29,
   29,   14,   14,   30,   30,    2,   32,   31,   31,   31,
   31,   31,   31,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,   33,   33,   33,   33,   35,
   34,   34,    6,    6,    7,    7,    7,    8,    8,    8,
    9,    9,   10,   10,   10,   11,   12,   12,   12,   12,
   12,   12,   12,   12,   12,   12,   12,   12,   12,   12,
   12,   12,   12,   13,   13,   15,    5,    5,    5,    5,
    5,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,   18,   18,   17,   17,   17,   16,   16,   16,
   16,   16,   16,   16,   16,   16,   16,   19,   20,   21,
   22,   27,   27,   26,   23,   23,
};
static short yylen[] = {                                         2,
    3,    4,    4,    5,    1,    2,    5,    1,    2,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    5,    6,
    7,    1,    3,    3,    4,    3,    3,    3,    5,    4,
    5,    4,    5,    1,    1,    1,    1,    2,    2,    2,
    2,    1,    1,    1,    1,    5,    4,    6,    5,    1,
    4,    4,    1,    2,    5,    4,    1,    1,    2,    1,
    5,    1,    1,    2,    1,    9,    1,    3,    3,    2,
    2,    2,    2,    2,    1,    1,    1,    1,    4,    4,
    3,    2,    0,    3,    3,    3,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    3,    1,    1,    2,    0,    1,    2,    2,
    1,    1,    1,    1,    1,    1,    1,    5,    2,    5,
    9,    4,    5,    1,    1,    2,
};
static short yydefred[] = {                                      0,
    5,    0,    0,    0,    0,    0,    0,    0,   18,    0,
    0,    0,    0,    0,   34,   35,   36,   37,   42,   43,
   44,   45,    0,  145,    0,    0,    0,   17,    8,   10,
   11,   12,   13,   14,   15,   16,    0,    0,    0,    0,
    0,    0,    0,    0,   38,   39,   40,   41,    0,    0,
    0,  146,    0,    0,    0,    0,   53,    9,    0,    0,
    0,  142,   27,    0,    0,    0,   24,    0,    0,    0,
    0,    0,    0,   28,    0,    0,    0,    0,    0,   57,
   54,    0,    2,    0,    7,  143,   51,   52,    0,   25,
    0,    0,    0,   47,    0,    0,    0,    0,   30,    0,
   32,    0,    0,  124,   75,    0,   76,    0,    0,    0,
   89,   90,    0,    0,   87,   88,   91,   77,  135,    0,
    0,    0,    0,    0,    0,    0,    0,  125,    0,  128,
  131,  132,  133,  134,  136,    4,   26,   22,    0,   19,
    0,   46,   49,    0,   29,   31,   33,   60,    0,    0,
   58,    0,    0,    0,    0,    0,    0,    0,  139,    0,
    0,  130,    0,    0,  129,  112,  110,  111,    0,  102,
  103,   94,   73,   74,   93,   92,   95,   96,   97,   98,
  100,  101,   99,  106,  107,  104,  105,  108,  109,  113,
  114,  118,  117,  115,  116,  119,  120,  121,  122,    0,
    0,   82,    0,   56,  126,    0,    0,   20,   48,    0,
   62,   55,   59,    0,    0,  123,   81,    0,    0,    0,
    0,    0,    0,    0,    0,   21,   23,    0,   79,   80,
    0,    0,    0,   86,   65,    0,    0,   63,  138,  140,
    0,    0,   61,   64,    0,    0,    0,    0,    0,    0,
  141,    0,    0,    0,   66,
};
static short yydgoto[] = {                                       4,
   25,   68,  200,  201,  125,   56,   57,  150,  151,  237,
  238,  126,  127,  139,  202,  128,  129,  130,  131,  132,
  133,  134,   26,    5,   27,   83,  135,   29,   30,   31,
   32,   33,   34,   35,   36,
};
static short yysindex[] = {                                   -253,
    0, -242, -235,    0,  112, -208, -236, -267,    0, -181,
 -225, -195, -172, -127,    0,    0,    0,    0,    0,    0,
    0,    0, -170,    0, -246, -220,   49,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  112, -203, -252, -146,
 -132, -129, -176, -258,    0,    0,    0,    0, -194, -238,
 -124,    0,    0, -120, -136, -243,    0,    0,   49, -133,
 -182,    0,    0, -116, -107,  -93,    0, -105, -261, -140,
 -103,  -90, -244,    0,  -88, -160, -143,  -97,  -56,    0,
    0, -220,    0, -243,    0,    0,    0,    0, -114,    0,
 -152,  -89, -141,    0,  -87,  -86,  -78,  -85,    0,  -84,
    0,  -77, -118,    0,    0,  -75,    0,  -68,  -56,  -63,
    0,    0,  -63,  -63,    0,    0,    0,    0,    0,  -67,
  -56,  -65,  -64,  -60,  -63,  464,  -62,    0, -228,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -248,    0,
  -58,    0,    0,  -57,    0,    0,    0,    0,  -43, -230,
    0,  -63,  -63, -151,  522, 1276, 1276,  -63,    0,  -63,
  -63,    0, 1276,  -63,    0,    0,    0,    0,  -63,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -63,
  -63,    0,  -63,    0,    0,  -45,  -96,    0,    0,  -41,
    0,    0,    0,  580,  638,    0,    0,  696,  754,  812,
  288, 1044, 1276, 1044, 1044,    0,    0, -237,    0,    0,
  -56,  -56,  -63,    0,    0,  -44, -207,    0,    0,    0,
  870,  -63,    0,    0,  -63,  928,  986,  -38,  -56,  -56,
    0, -106,  -19,  -14,    0,
};
static short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,  126,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   64,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    1,    0,    0,  247,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1102,    0,
    0,  248,    0,  249,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  170,    0,    0, 1102, 1160,
    0,    0,  347,  347,    0,    0,    0,    0,    0,    0,
 1218,    0,    0,    0,  347,    0,  229,    0, 1218,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 1160, 1160, 1218,    0, 1335, 1353, 1160,    0, 1160,
 1218,    0, 1395,  406,    0,    0,    0,    0,  347,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  347,
  347,    0,  347,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, -190, 1413, -155, -145,    0,    0,    0,    0,    0,
 1218, 1218, 1218,    0,    0,    0,    0,    0,    0,    0,
    0, 1160,    0,    0, 1160,    0,    0,    0, 1218, 1102,
    0, 1218,    0,    0,    0,
};
static short yygindex[] = {                                      0,
    0,   10,    0,    0,    0,  191,  -36,    0,  101,    0,
   16, -108,    0,    0,    0, -117, -109,    0,    0,    0,
    0,    0,  -33,  250,  217,  171,   57,  -16,    0,    0,
    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 1720
static short yytable[] = {                                     154,
   57,  155,    1,  159,  156,  157,   61,   91,   66,    2,
   58,  205,   80,   50,   54,   96,  163,    7,  235,   81,
   55,  206,   82,    8,   69,  211,  149,  104,   66,  207,
  105,  106,  107,   74,   75,  108,  205,   38,   97,  212,
  109,  204,   58,  214,  215,  110,  236,   81,   51,  218,
   82,  219,  220,   70,    2,  221,    6,   39,   73,   76,
  222,   28,  243,   92,   43,   71,  111,  112,  113,  114,
  115,  116,   66,   41,   42,   84,  236,   40,    3,  117,
   62,   84,   24,   28,   84,  100,  102,   44,   72,   49,
   66,  223,  224,   28,  225,   67,  118,  119,  120,  121,
  122,  123,  124,    3,  104,   52,   66,  105,  106,  107,
   69,   99,  108,  239,  240,   28,   69,  109,  216,   69,
   85,   60,  110,   66,  241,   63,   85,   64,  101,   85,
   65,  251,   79,  246,  205,   77,  247,  148,  149,   78,
  252,   85,   93,  111,  112,  113,  114,  115,  116,  104,
   86,  137,  105,  106,  107,   87,  117,  108,   45,   46,
   47,   48,  109,  253,   88,   89,   90,  110,   94,   95,
   98,  103,  138,  118,  119,  120,  121,  122,  123,  124,
    3,  144,  140,  141,  142,  143,  145,  146,  111,  112,
  113,  114,  115,  116,  147,  105,  106,  107,  152,  104,
  108,  117,  105,  106,  107,  153,  158,  108,  160,  161,
  110,  162,  109,  208,  209,  203,  210,  110,  118,  119,
  120,  121,  122,  123,  124,    3,  226,  228,  227,  242,
  250,  111,  112,  113,  114,  115,  116,  254,  111,  112,
  113,  114,  115,  116,  117,  255,    1,  144,    3,   84,
  213,  117,  244,   59,  136,   37,   18,    0,   18,    0,
    0,  118,   18,    0,   18,   18,    0,    0,  118,  119,
  120,  121,  122,  123,  124,    3,    0,    0,    0,    0,
    0,   18,   18,    0,    0,   18,   18,   18,   18,   18,
   18,   18,   18,   18,   18,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   53,    0,   54,    0,    0,    0,
   10,    0,   55,   11,    0,    0,    0,    0,    0,   50,
    0,   50,    0,    0,    0,   50,   18,   50,   50,   12,
   13,    0,   18,   14,   15,   16,   17,   18,   19,   20,
   21,   22,   23,    0,   50,   50,    0,    0,   50,   50,
   50,   50,   50,   50,   50,   50,   50,   50,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    9,    0,    0,
    0,    0,    0,   10,   24,    0,   11,    0,    0,    0,
    3,    6,    0,    0,    0,    0,    0,    6,    0,    0,
    6,    0,   12,   13,    0,   50,   14,   15,   16,   17,
   18,   19,   20,   21,   22,   23,    6,    6,    0,    0,
    6,    6,    6,    6,    6,    6,    6,    6,    6,    6,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   78,   78,   24,    0,    0,
    0,   78,   78,    3,   78,   78,   78,   78,   78,   78,
    0,    6,    0,    0,    0,    0,    0,    6,    0,    0,
    0,    0,    0,    0,   78,    0,   78,   78,   78,   78,
   78,   78,   78,   78,   78,   78,   78,    0,   78,   78,
   78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
   78,   78,   78,   78,   67,   67,    0,    0,    0,    0,
   67,   67,    0,   67,   67,   67,    0,   67,   67,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   67,    0,   67,   67,   67,   67,   67,
   67,   67,   67,   67,   67,   67,    0,   67,   67,   67,
   67,   67,   67,   67,   67,   67,   67,   67,   67,   67,
   67,   67,   67,  234,  164,    0,    0,    0,    0,    0,
  166,    0,    0,  167,  168,  169,  170,  171,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  172,    0,  173,  174,  175,  176,  177,  178,
  179,  180,  181,  182,  183,    0,  184,  185,  186,  187,
  188,  189,  190,  191,  192,  193,  194,  195,  196,  197,
  198,  199,   83,   83,    0,    0,    0,    0,   83,   83,
    0,   83,   83,   83,   83,   83,   83,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   83,   83,   83,
   83,   83,   83,   83,    0,   83,   83,   83,   83,   83,
   83,   83,   83,   83,   83,   83,   83,   83,   83,   83,
   83,   83,   83,    0,    0,    0,    0,    0,   83,    0,
    0,   83,   83,   83,   83,   83,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   83,   83,   83,   83,
   83,   83,   83,    0,   83,   83,   83,   83,   83,   83,
   83,   83,   83,   83,   83,   83,   83,   83,   83,   83,
  164,    0,    0,    0,    0,  165,  166,    0,    0,  167,
  168,  169,  170,  171,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  172,    0,
  173,  174,  175,  176,  177,  178,  179,  180,  181,  182,
  183,    0,  184,  185,  186,  187,  188,  189,  190,  191,
  192,  193,  194,  195,  196,  197,  198,  199,  164,    0,
    0,    0,    0,    0,  166,    0,  217,  167,  168,  169,
  170,  171,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  172,    0,  173,  174,
  175,  176,  177,  178,  179,  180,  181,  182,  183,    0,
  184,  185,  186,  187,  188,  189,  190,  191,  192,  193,
  194,  195,  196,  197,  198,  199,  164,    0,    0,    0,
    0,    0,  166,    0,  229,  167,  168,  169,  170,  171,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  172,    0,  173,  174,  175,  176,
  177,  178,  179,  180,  181,  182,  183,    0,  184,  185,
  186,  187,  188,  189,  190,  191,  192,  193,  194,  195,
  196,  197,  198,  199,  164,    0,    0,    0,    0,    0,
  166,    0,  230,  167,  168,  169,  170,  171,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  172,    0,  173,  174,  175,  176,  177,  178,
  179,  180,  181,  182,  183,    0,  184,  185,  186,  187,
  188,  189,  190,  191,  192,  193,  194,  195,  196,  197,
  198,  199,  164,    0,    0,    0,    0,    0,  166,    0,
  231,  167,  168,  169,  170,  171,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  172,    0,  173,  174,  175,  176,  177,  178,  179,  180,
  181,  182,  183,    0,  184,  185,  186,  187,  188,  189,
  190,  191,  192,  193,  194,  195,  196,  197,  198,  199,
  164,    0,    0,    0,    0,    0,  166,    0,  232,  167,
  168,  169,  170,  171,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  172,    0,
  173,  174,  175,  176,  177,  178,  179,  180,  181,  182,
  183,    0,  184,  185,  186,  187,  188,  189,  190,  191,
  192,  193,  194,  195,  196,  197,  198,  199,  164,    0,
    0,    0,    0,  233,  166,    0,    0,  167,  168,  169,
  170,  171,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  172,    0,  173,  174,
  175,  176,  177,  178,  179,  180,  181,  182,  183,    0,
  184,  185,  186,  187,  188,  189,  190,  191,  192,  193,
  194,  195,  196,  197,  198,  199,  164,    0,    0,    0,
    0,  245,  166,    0,    0,  167,  168,  169,  170,  171,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  172,    0,  173,  174,  175,  176,
  177,  178,  179,  180,  181,  182,  183,    0,  184,  185,
  186,  187,  188,  189,  190,  191,  192,  193,  194,  195,
  196,  197,  198,  199,  164,    0,    0,    0,    0,    0,
  166,    0,  248,  167,  168,  169,  170,  171,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  172,    0,  173,  174,  175,  176,  177,  178,
  179,  180,  181,  182,  183,    0,  184,  185,  186,  187,
  188,  189,  190,  191,  192,  193,  194,  195,  196,  197,
  198,  199,  164,    0,    0,    0,    0,    0,  166,    0,
  249,  167,  168,  169,  170,  171,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  172,    0,  173,  174,  175,  176,  177,  178,  179,  180,
  181,  182,  183,    0,  184,  185,  186,  187,  188,  189,
  190,  191,  192,  193,  194,  195,  196,  197,  198,  199,
  164,    0,    0,    0,    0,    0,  166,    0,    0,  167,
  168,  169,  170,  171,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  172,    0,
  173,  174,  175,  176,  177,  178,  179,  180,  181,  182,
  183,    0,  184,  185,  186,  187,  188,  189,  190,  191,
  192,  193,  194,  195,  196,  197,  198,  199,   83,    0,
    0,  127,    0,   83,   83,    0,    0,   83,   83,   83,
   83,   83,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   83,   83,   83,   83,   83,   83,   83,    0,
   83,   83,   83,   83,   83,   83,   83,   83,   83,   83,
   83,   83,   83,   83,   83,   83,   83,    0,    0,    0,
    0,    0,   83,    0,   83,   83,   83,   83,   83,   83,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   83,   83,   83,   83,   83,   83,   83,    0,   83,   83,
   83,   83,   83,   83,   83,   83,   83,   83,   83,   83,
   83,   83,   83,   83,   83,    0,    0,    0,    0,   83,
   83,    0,    0,   83,   83,   83,   83,   83,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   83,   83,
   83,   83,   83,   83,   83,    0,   83,   83,   83,   83,
   83,   83,   83,   83,   83,   83,   83,   83,   83,   83,
   83,   83,  164,    0,    0,    0,    0,    0,    0,    0,
    0,  167,  168,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  173,  174,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  184,  185,  186,  187,  188,  189,
  190,  191,  192,  193,  194,  195,  196,  197,  198,  199,
   71,    0,    0,    0,    0,    0,   71,   71,    0,   71,
    0,    0,   71,   71,   71,    0,    0,    0,   72,    0,
    0,    0,    0,    0,   72,   72,    0,   72,    0,   71,
   72,   72,   72,   71,   71,   71,   71,   71,   71,   71,
   71,   71,    0,    0,    0,    0,    0,   72,    0,    0,
    0,   72,   72,   72,   72,   72,   72,   72,   72,   72,
   70,    0,    0,    0,    0,    0,   70,   70,    0,   70,
    0,    0,   70,   70,   70,    0,    0,    0,   68,    0,
    0,    0,    0,    0,   68,   68,    0,   68,    0,   70,
   68,   68,   68,   70,   70,   70,   70,   70,   70,   70,
   70,   70,    0,    0,    0,    0,    0,   68,    0,    0,
    0,   68,   68,   68,   68,   68,   68,   68,   68,   68,
};
static short yycheck[] = {                                     109,
    0,  110,  256,  121,  113,  114,  259,  269,  267,  263,
   27,  129,  256,  260,  258,  260,  125,  260,  256,   56,
  264,  270,   56,  259,  283,  256,  257,  256,  267,  278,
  259,  260,  261,  272,  273,  264,  154,  274,  283,  270,
  269,  270,   59,  152,  153,  274,  284,   84,  295,  158,
   84,  160,  161,   44,  263,  164,    0,  325,   49,   50,
  169,    5,  270,  325,  260,  260,  295,  296,  297,  298,
  299,  300,  267,  299,  300,  266,  284,  259,  332,  308,
  333,  272,  326,   27,  275,   76,   77,  260,  283,  260,
  267,  200,  201,   37,  203,  272,  325,  326,  327,  328,
  329,  330,  331,  332,  256,  326,  267,  259,  260,  261,
  266,  272,  264,  231,  232,   59,  272,  269,  270,  275,
  266,  325,  274,  267,  233,  272,  272,  260,  272,  275,
  260,  249,  269,  242,  252,  260,  245,  256,  257,  260,
  250,  275,  283,  295,  296,  297,  298,  299,  300,  256,
  333,  266,  259,  260,  261,  272,  308,  264,  286,  287,
  288,  289,  269,  270,  272,  259,  272,  274,  272,  260,
  259,  269,  325,  325,  326,  327,  328,  329,  330,  331,
  332,  260,  272,  325,  272,  272,  272,  272,  295,  296,
  297,  298,  299,  300,  272,  259,  260,  261,  274,  256,
  264,  308,  259,  260,  261,  274,  274,  264,  274,  274,
  274,  272,  269,  272,  272,  278,  260,  274,  325,  326,
  327,  328,  329,  330,  331,  332,  272,  269,  325,  274,
  269,  295,  296,  297,  298,  299,  300,  257,  295,  296,
  297,  298,  299,  300,  308,  260,    0,    0,    0,   59,
  150,  308,  237,   37,   84,    6,  256,   -1,  258,   -1,
   -1,  325,  262,   -1,  264,  265,   -1,   -1,  325,  326,
  327,  328,  329,  330,  331,  332,   -1,   -1,   -1,   -1,
   -1,  281,  282,   -1,   -1,  285,  286,  287,  288,  289,
  290,  291,  292,  293,  294,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  256,   -1,  258,   -1,   -1,   -1,
  262,   -1,  264,  265,   -1,   -1,   -1,   -1,   -1,  256,
   -1,  258,   -1,   -1,   -1,  262,  326,  264,  265,  281,
  282,   -1,  332,  285,  286,  287,  288,  289,  290,  291,
  292,  293,  294,   -1,  281,  282,   -1,   -1,  285,  286,
  287,  288,  289,  290,  291,  292,  293,  294,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  256,   -1,   -1,
   -1,   -1,   -1,  262,  326,   -1,  265,   -1,   -1,   -1,
  332,  256,   -1,   -1,   -1,   -1,   -1,  262,   -1,   -1,
  265,   -1,  281,  282,   -1,  332,  285,  286,  287,  288,
  289,  290,  291,  292,  293,  294,  281,  282,   -1,   -1,
  285,  286,  287,  288,  289,  290,  291,  292,  293,  294,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  266,  267,  326,   -1,   -1,
   -1,  272,  273,  332,  275,  276,  277,  278,  279,  280,
   -1,  326,   -1,   -1,   -1,   -1,   -1,  332,   -1,   -1,
   -1,   -1,   -1,   -1,  295,   -1,  297,  298,  299,  300,
  301,  302,  303,  304,  305,  306,  307,   -1,  309,  310,
  311,  312,  313,  314,  315,  316,  317,  318,  319,  320,
  321,  322,  323,  324,  266,  267,   -1,   -1,   -1,   -1,
  272,  273,   -1,  275,  276,  277,   -1,  279,  280,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  295,   -1,  297,  298,  299,  300,  301,
  302,  303,  304,  305,  306,  307,   -1,  309,  310,  311,
  312,  313,  314,  315,  316,  317,  318,  319,  320,  321,
  322,  323,  324,  266,  267,   -1,   -1,   -1,   -1,   -1,
  273,   -1,   -1,  276,  277,  278,  279,  280,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  295,   -1,  297,  298,  299,  300,  301,  302,
  303,  304,  305,  306,  307,   -1,  309,  310,  311,  312,
  313,  314,  315,  316,  317,  318,  319,  320,  321,  322,
  323,  324,  266,  267,   -1,   -1,   -1,   -1,  272,  273,
   -1,  275,  276,  277,  278,  279,  280,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  301,  302,  303,
  304,  305,  306,  307,   -1,  309,  310,  311,  312,  313,
  314,  315,  316,  317,  318,  319,  320,  321,  322,  323,
  324,  266,  267,   -1,   -1,   -1,   -1,   -1,  273,   -1,
   -1,  276,  277,  278,  279,  280,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  301,  302,  303,  304,
  305,  306,  307,   -1,  309,  310,  311,  312,  313,  314,
  315,  316,  317,  318,  319,  320,  321,  322,  323,  324,
  267,   -1,   -1,   -1,   -1,  272,  273,   -1,   -1,  276,
  277,  278,  279,  280,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  295,   -1,
  297,  298,  299,  300,  301,  302,  303,  304,  305,  306,
  307,   -1,  309,  310,  311,  312,  313,  314,  315,  316,
  317,  318,  319,  320,  321,  322,  323,  324,  267,   -1,
   -1,   -1,   -1,   -1,  273,   -1,  275,  276,  277,  278,
  279,  280,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  295,   -1,  297,  298,
  299,  300,  301,  302,  303,  304,  305,  306,  307,   -1,
  309,  310,  311,  312,  313,  314,  315,  316,  317,  318,
  319,  320,  321,  322,  323,  324,  267,   -1,   -1,   -1,
   -1,   -1,  273,   -1,  275,  276,  277,  278,  279,  280,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  295,   -1,  297,  298,  299,  300,
  301,  302,  303,  304,  305,  306,  307,   -1,  309,  310,
  311,  312,  313,  314,  315,  316,  317,  318,  319,  320,
  321,  322,  323,  324,  267,   -1,   -1,   -1,   -1,   -1,
  273,   -1,  275,  276,  277,  278,  279,  280,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  295,   -1,  297,  298,  299,  300,  301,  302,
  303,  304,  305,  306,  307,   -1,  309,  310,  311,  312,
  313,  314,  315,  316,  317,  318,  319,  320,  321,  322,
  323,  324,  267,   -1,   -1,   -1,   -1,   -1,  273,   -1,
  275,  276,  277,  278,  279,  280,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  295,   -1,  297,  298,  299,  300,  301,  302,  303,  304,
  305,  306,  307,   -1,  309,  310,  311,  312,  313,  314,
  315,  316,  317,  318,  319,  320,  321,  322,  323,  324,
  267,   -1,   -1,   -1,   -1,   -1,  273,   -1,  275,  276,
  277,  278,  279,  280,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  295,   -1,
  297,  298,  299,  300,  301,  302,  303,  304,  305,  306,
  307,   -1,  309,  310,  311,  312,  313,  314,  315,  316,
  317,  318,  319,  320,  321,  322,  323,  324,  267,   -1,
   -1,   -1,   -1,  272,  273,   -1,   -1,  276,  277,  278,
  279,  280,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  295,   -1,  297,  298,
  299,  300,  301,  302,  303,  304,  305,  306,  307,   -1,
  309,  310,  311,  312,  313,  314,  315,  316,  317,  318,
  319,  320,  321,  322,  323,  324,  267,   -1,   -1,   -1,
   -1,  272,  273,   -1,   -1,  276,  277,  278,  279,  280,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  295,   -1,  297,  298,  299,  300,
  301,  302,  303,  304,  305,  306,  307,   -1,  309,  310,
  311,  312,  313,  314,  315,  316,  317,  318,  319,  320,
  321,  322,  323,  324,  267,   -1,   -1,   -1,   -1,   -1,
  273,   -1,  275,  276,  277,  278,  279,  280,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  295,   -1,  297,  298,  299,  300,  301,  302,
  303,  304,  305,  306,  307,   -1,  309,  310,  311,  312,
  313,  314,  315,  316,  317,  318,  319,  320,  321,  322,
  323,  324,  267,   -1,   -1,   -1,   -1,   -1,  273,   -1,
  275,  276,  277,  278,  279,  280,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  295,   -1,  297,  298,  299,  300,  301,  302,  303,  304,
  305,  306,  307,   -1,  309,  310,  311,  312,  313,  314,
  315,  316,  317,  318,  319,  320,  321,  322,  323,  324,
  267,   -1,   -1,   -1,   -1,   -1,  273,   -1,   -1,  276,
  277,  278,  279,  280,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  295,   -1,
  297,  298,  299,  300,  301,  302,  303,  304,  305,  306,
  307,   -1,  309,  310,  311,  312,  313,  314,  315,  316,
  317,  318,  319,  320,  321,  322,  323,  324,  267,   -1,
   -1,  270,   -1,  272,  273,   -1,   -1,  276,  277,  278,
  279,  280,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  301,  302,  303,  304,  305,  306,  307,   -1,
  309,  310,  311,  312,  313,  314,  315,  316,  317,  318,
  319,  320,  321,  322,  323,  324,  267,   -1,   -1,   -1,
   -1,   -1,  273,   -1,  275,  276,  277,  278,  279,  280,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  301,  302,  303,  304,  305,  306,  307,   -1,  309,  310,
  311,  312,  313,  314,  315,  316,  317,  318,  319,  320,
  321,  322,  323,  324,  267,   -1,   -1,   -1,   -1,  272,
  273,   -1,   -1,  276,  277,  278,  279,  280,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  301,  302,
  303,  304,  305,  306,  307,   -1,  309,  310,  311,  312,
  313,  314,  315,  316,  317,  318,  319,  320,  321,  322,
  323,  324,  267,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  276,  277,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  297,  298,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  309,  310,  311,  312,  313,  314,
  315,  316,  317,  318,  319,  320,  321,  322,  323,  324,
  266,   -1,   -1,   -1,   -1,   -1,  272,  273,   -1,  275,
   -1,   -1,  278,  279,  280,   -1,   -1,   -1,  266,   -1,
   -1,   -1,   -1,   -1,  272,  273,   -1,  275,   -1,  295,
  278,  279,  280,  299,  300,  301,  302,  303,  304,  305,
  306,  307,   -1,   -1,   -1,   -1,   -1,  295,   -1,   -1,
   -1,  299,  300,  301,  302,  303,  304,  305,  306,  307,
  266,   -1,   -1,   -1,   -1,   -1,  272,  273,   -1,  275,
   -1,   -1,  278,  279,  280,   -1,   -1,   -1,  266,   -1,
   -1,   -1,   -1,   -1,  272,  273,   -1,  275,   -1,  295,
  278,  279,  280,  299,  300,  301,  302,  303,  304,  305,
  306,  307,   -1,   -1,   -1,   -1,   -1,  295,   -1,   -1,
   -1,  299,  300,  301,  302,  303,  304,  305,  306,  307,
};
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 335
#if YYDEBUG
static char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"STATE","STATE_SET","NUMBER",
"NAME","CHAR_CONST","DEBUG_PRINT","PROGRAM","EXIT","OPTION","R_SQ_BRACKET",
"L_SQ_BRACKET","BAD_CHAR","L_BRACKET","R_BRACKET","COLON","SEMI_COLON","EQUAL",
"L_PAREN","R_PAREN","PERIOD","POINTER","COMMA","OR","AND","MONITOR","ASSIGN",
"TO","WHEN","UNSIGNED","CHAR","SHORT","INT","LONG","FLOAT","DOUBLE",
"STRING_DECL","EVFLAG","SYNC","ASTERISK","AMPERSAND","AUTO_INCR","AUTO_DECR",
"PLUS","MINUS","SLASH","GT","GE","EQ","LE","LT","NE","NOT","BIT_OR","BIT_AND",
"L_SHIFT","R_SHIFT","COMPLEMENT","MODULO","PLUS_EQUAL","MINUS_EQUAL",
"MULT_EQUAL","DIV_EQUAL","AND_EQUAL","OR_EQUAL","MODULO_EQUAL","LEFT_EQUAL",
"RIGHT_EQUAL","CMPL_EQUAL","STRING","C_STMT","IF","ELSE","WHILE","FOR","BREAK",
"PP_SYMBOL","CR","UOP","SUBSCRIPT",
};
static char *yyrule[] = {
"$accept : state_program",
"state_program : program_name definitions state_set_list",
"state_program : program_name definitions state_set_list global_c",
"state_program : pp_code program_name definitions state_set_list",
"state_program : pp_code program_name definitions state_set_list global_c",
"state_program : error",
"program_name : PROGRAM NAME",
"program_name : PROGRAM NAME L_PAREN STRING R_PAREN",
"definitions : defn_stmt",
"definitions : definitions defn_stmt",
"defn_stmt : assign_stmt",
"defn_stmt : monitor_stmt",
"defn_stmt : decl_stmt",
"defn_stmt : debug_stmt",
"defn_stmt : sync_stmt",
"defn_stmt : option_stmt",
"defn_stmt : defn_c_stmt",
"defn_stmt : pp_code",
"defn_stmt : error",
"assign_stmt : ASSIGN NAME TO STRING SEMI_COLON",
"assign_stmt : ASSIGN NAME subscript TO STRING SEMI_COLON",
"assign_stmt : ASSIGN NAME TO L_BRACKET assign_list R_BRACKET SEMI_COLON",
"assign_list : STRING",
"assign_list : assign_list COMMA STRING",
"monitor_stmt : MONITOR NAME SEMI_COLON",
"monitor_stmt : MONITOR NAME subscript SEMI_COLON",
"subscript : L_SQ_BRACKET NUMBER R_SQ_BRACKET",
"debug_stmt : DEBUG_PRINT NUMBER SEMI_COLON",
"decl_stmt : type NAME SEMI_COLON",
"decl_stmt : type NAME EQUAL NUMBER SEMI_COLON",
"decl_stmt : type NAME subscript SEMI_COLON",
"decl_stmt : type NAME subscript subscript SEMI_COLON",
"decl_stmt : type ASTERISK NAME SEMI_COLON",
"decl_stmt : type ASTERISK NAME subscript SEMI_COLON",
"type : CHAR",
"type : SHORT",
"type : INT",
"type : LONG",
"type : UNSIGNED CHAR",
"type : UNSIGNED SHORT",
"type : UNSIGNED INT",
"type : UNSIGNED LONG",
"type : FLOAT",
"type : DOUBLE",
"type : STRING_DECL",
"type : EVFLAG",
"sync_stmt : SYNC NAME TO NAME SEMI_COLON",
"sync_stmt : SYNC NAME NAME SEMI_COLON",
"sync_stmt : SYNC NAME subscript TO NAME SEMI_COLON",
"sync_stmt : SYNC NAME subscript NAME SEMI_COLON",
"defn_c_stmt : escaped_c_list",
"option_stmt : OPTION PLUS NAME SEMI_COLON",
"option_stmt : OPTION MINUS NAME SEMI_COLON",
"state_set_list : state_set",
"state_set_list : state_set_list state_set",
"state_set : STATE_SET NAME L_BRACKET state_list R_BRACKET",
"state_set : EXIT L_BRACKET stmt_list R_BRACKET",
"state_set : error",
"state_list : state",
"state_list : state_list state",
"state_list : error",
"state : STATE NAME L_BRACKET transition_list R_BRACKET",
"state : error",
"transition_list : transition",
"transition_list : transition_list transition",
"transition_list : error",
"transition : WHEN L_PAREN expr R_PAREN L_BRACKET stmt_list R_BRACKET STATE NAME",
"expr : compound_expr",
"expr : expr binop expr",
"expr : expr asgnop expr",
"expr : unop expr",
"expr : AUTO_INCR expr",
"expr : AUTO_DECR expr",
"expr : expr AUTO_INCR",
"expr : expr AUTO_DECR",
"expr : NUMBER",
"expr : CHAR_CONST",
"expr : STRING",
"expr : NAME",
"expr : NAME L_PAREN expr R_PAREN",
"expr : EXIT L_PAREN expr R_PAREN",
"expr : L_PAREN expr R_PAREN",
"expr : expr bracked_expr",
"expr :",
"compound_expr : expr COMMA expr",
"compound_expr : compound_expr COMMA expr",
"bracked_expr : L_SQ_BRACKET expr R_SQ_BRACKET",
"unop : PLUS",
"unop : MINUS",
"unop : ASTERISK",
"unop : AMPERSAND",
"unop : NOT",
"binop : MINUS",
"binop : PLUS",
"binop : ASTERISK",
"binop : SLASH",
"binop : GT",
"binop : GE",
"binop : EQ",
"binop : NE",
"binop : LE",
"binop : LT",
"binop : OR",
"binop : AND",
"binop : L_SHIFT",
"binop : R_SHIFT",
"binop : BIT_OR",
"binop : BIT_AND",
"binop : COMPLEMENT",
"binop : MODULO",
"binop : PERIOD",
"binop : POINTER",
"asgnop : EQUAL",
"asgnop : PLUS_EQUAL",
"asgnop : MINUS_EQUAL",
"asgnop : AND_EQUAL",
"asgnop : OR_EQUAL",
"asgnop : DIV_EQUAL",
"asgnop : MULT_EQUAL",
"asgnop : MODULO_EQUAL",
"asgnop : LEFT_EQUAL",
"asgnop : RIGHT_EQUAL",
"asgnop : CMPL_EQUAL",
"compound_stmt : L_BRACKET stmt_list R_BRACKET",
"compound_stmt : error",
"stmt_list : statement",
"stmt_list : stmt_list statement",
"stmt_list :",
"statement : compound_stmt",
"statement : expr SEMI_COLON",
"statement : BREAK SEMI_COLON",
"statement : if_stmt",
"statement : else_stmt",
"statement : while_stmt",
"statement : for_stmt",
"statement : C_STMT",
"statement : pp_code",
"statement : error",
"if_stmt : IF L_PAREN expr R_PAREN statement",
"else_stmt : ELSE statement",
"while_stmt : WHILE L_PAREN expr R_PAREN statement",
"for_stmt : FOR L_PAREN expr SEMI_COLON expr SEMI_COLON expr R_PAREN statement",
"pp_code : PP_SYMBOL NUMBER STRING CR",
"pp_code : PP_SYMBOL NUMBER STRING NUMBER CR",
"global_c : escaped_c_list",
"escaped_c_list : C_STMT",
"escaped_c_list : escaped_c_list C_STMT",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
static int yydebug;
static int yynerrs;
static int yyerrflag;
static int yychar;
static short *yyssp;
static YYSTYPE *yyvsp;
static YYSTYPE yyval;
static YYSTYPE yylval;
static short yyss[YYSTACKSIZE];
static YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 378 "../snc.y"
#include	"snc_lex.c"

static int yyparse (void);

/* yyparse() is static, so we create global access to it */
void Global_yyparse (void)
{
	yyparse ();
}

#line 840 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
#ifdef __STDC__
static int
yyparse(void)
#else
static int
yyparse()
#endif
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 99 "../snc.y"
{ program(yyvsp[0].pexpr); }
break;
case 2:
#line 100 "../snc.y"
{ program(yyvsp[-1].pexpr); }
break;
case 3:
#line 101 "../snc.y"
{ program(yyvsp[0].pexpr); }
break;
case 4:
#line 102 "../snc.y"
{ program(yyvsp[-1].pexpr); }
break;
case 5:
#line 103 "../snc.y"
{ snc_err("state program"); }
break;
case 6:
#line 107 "../snc.y"
{ program_name(yyvsp[0].pchar, ""); }
break;
case 7:
#line 108 "../snc.y"
{ program_name(yyvsp[-3].pchar, yyvsp[-1].pchar); }
break;
case 18:
#line 125 "../snc.y"
{ snc_err("definitions/declarations"); }
break;
case 19:
#line 129 "../snc.y"
{ assign_single(yyvsp[-3].pchar, yyvsp[-1].pchar); }
break;
case 20:
#line 132 "../snc.y"
{ assign_subscr(yyvsp[-4].pchar, yyvsp[-3].pchar, yyvsp[-1].pchar); }
break;
case 21:
#line 136 "../snc.y"
{ assign_list(yyvsp[-5].pchar, yyvsp[-2].pexpr); }
break;
case 22:
#line 140 "../snc.y"
{ yyval.pexpr = expression(E_STRING, yyvsp[0].pchar, 0, 0); }
break;
case 23:
#line 142 "../snc.y"
{ yyval.pexpr = link_expr(yyvsp[-2].pexpr, expression(E_STRING, yyvsp[0].pchar, 0, 0)); }
break;
case 24:
#line 146 "../snc.y"
{ monitor_stmt(yyvsp[-1].pchar, NULL); }
break;
case 25:
#line 147 "../snc.y"
{ monitor_stmt(yyvsp[-2].pchar, yyvsp[-1].pchar); }
break;
case 26:
#line 151 "../snc.y"
{ yyval.pchar = yyvsp[-1].pchar; }
break;
case 27:
#line 155 "../snc.y"
{ set_debug_print(yyvsp[-1].pchar); }
break;
case 28:
#line 161 "../snc.y"
{ decl_stmt(yyvsp[-2].ival, VC_SIMPLE,  yyvsp[-1].pchar,  NULL, NULL, NULL); }
break;
case 29:
#line 164 "../snc.y"
{ decl_stmt(yyvsp[-4].ival, VC_SIMPLE,  yyvsp[-3].pchar,  NULL, NULL, yyvsp[-1].pchar  ); }
break;
case 30:
#line 167 "../snc.y"
{ decl_stmt(yyvsp[-3].ival, VC_ARRAY1,  yyvsp[-2].pchar,  yyvsp[-1].pchar,   NULL, NULL); }
break;
case 31:
#line 170 "../snc.y"
{ decl_stmt(yyvsp[-4].ival, VC_ARRAY2,  yyvsp[-3].pchar,  yyvsp[-2].pchar,   yyvsp[-1].pchar,   NULL); }
break;
case 32:
#line 173 "../snc.y"
{ decl_stmt(yyvsp[-3].ival, VC_POINTER, yyvsp[-1].pchar,  NULL, NULL, NULL); }
break;
case 33:
#line 176 "../snc.y"
{ decl_stmt(yyvsp[-4].ival, VC_ARRAYP,  yyvsp[-2].pchar,  yyvsp[-1].pchar,   NULL, NULL); }
break;
case 34:
#line 180 "../snc.y"
{ yyval.ival = V_CHAR; }
break;
case 35:
#line 181 "../snc.y"
{ yyval.ival = V_SHORT; }
break;
case 36:
#line 182 "../snc.y"
{ yyval.ival = V_INT; }
break;
case 37:
#line 183 "../snc.y"
{ yyval.ival = V_LONG; }
break;
case 38:
#line 184 "../snc.y"
{ yyval.ival = V_UCHAR; }
break;
case 39:
#line 185 "../snc.y"
{ yyval.ival = V_USHORT; }
break;
case 40:
#line 186 "../snc.y"
{ yyval.ival = V_UINT; }
break;
case 41:
#line 187 "../snc.y"
{ yyval.ival = V_ULONG; }
break;
case 42:
#line 188 "../snc.y"
{ yyval.ival = V_FLOAT; }
break;
case 43:
#line 189 "../snc.y"
{ yyval.ival = V_DOUBLE; }
break;
case 44:
#line 190 "../snc.y"
{ yyval.ival = V_STRING; }
break;
case 45:
#line 191 "../snc.y"
{ yyval.ival = V_EVFLAG; }
break;
case 46:
#line 195 "../snc.y"
{ sync_stmt(yyvsp[-3].pchar, NULL, yyvsp[-1].pchar); }
break;
case 47:
#line 196 "../snc.y"
{ sync_stmt(yyvsp[-2].pchar, NULL, yyvsp[-1].pchar); }
break;
case 48:
#line 197 "../snc.y"
{ sync_stmt(yyvsp[-4].pchar, yyvsp[-3].pchar,   yyvsp[-1].pchar); }
break;
case 49:
#line 198 "../snc.y"
{ sync_stmt(yyvsp[-3].pchar, yyvsp[-2].pchar,   yyvsp[-1].pchar); }
break;
case 50:
#line 202 "../snc.y"
{ defn_c_stmt(yyvsp[0].pexpr); }
break;
case 51:
#line 206 "../snc.y"
{ option_stmt(yyvsp[-1].pchar, TRUE); }
break;
case 52:
#line 207 "../snc.y"
{ option_stmt(yyvsp[-1].pchar, FALSE); }
break;
case 53:
#line 211 "../snc.y"
{ yyval.pexpr = yyvsp[0].pexpr; }
break;
case 54:
#line 212 "../snc.y"
{ yyval.pexpr = link_expr(yyvsp[-1].pexpr, yyvsp[0].pexpr); }
break;
case 55:
#line 217 "../snc.y"
{ yyval.pexpr = expression(E_SS, yyvsp[-3].pchar, yyvsp[-1].pexpr, 0); }
break;
case 56:
#line 219 "../snc.y"
{ exit_code(yyvsp[-1].pexpr); yyval.pexpr = 0; }
break;
case 57:
#line 221 "../snc.y"
{ snc_err("state set"); }
break;
case 58:
#line 225 "../snc.y"
{ yyval.pexpr = yyvsp[0].pexpr; }
break;
case 59:
#line 226 "../snc.y"
{ yyval.pexpr = link_expr(yyvsp[-1].pexpr, yyvsp[0].pexpr); }
break;
case 60:
#line 227 "../snc.y"
{ snc_err("state set"); }
break;
case 61:
#line 232 "../snc.y"
{ yyval.pexpr = expression(E_STATE, yyvsp[-3].pchar, yyvsp[-1].pexpr, 0); }
break;
case 62:
#line 233 "../snc.y"
{ snc_err("state block"); }
break;
case 63:
#line 237 "../snc.y"
{ yyval.pexpr = yyvsp[0].pexpr; }
break;
case 64:
#line 238 "../snc.y"
{ yyval.pexpr = link_expr(yyvsp[-1].pexpr, yyvsp[0].pexpr); }
break;
case 65:
#line 239 "../snc.y"
{ snc_err("transition"); }
break;
case 66:
#line 244 "../snc.y"
{ yyval.pexpr = expression(E_WHEN, yyvsp[0].pchar, yyvsp[-6].pexpr, yyvsp[-3].pexpr); }
break;
case 67:
#line 249 "../snc.y"
{ yyval.pexpr = yyvsp[0].pexpr; }
break;
case 68:
#line 250 "../snc.y"
{ yyval.pexpr = expression(E_BINOP, yyvsp[-1].pchar, yyvsp[-2].pexpr, yyvsp[0].pexpr); }
break;
case 69:
#line 251 "../snc.y"
{ yyval.pexpr = expression(E_ASGNOP, yyvsp[-1].pchar, yyvsp[-2].pexpr, yyvsp[0].pexpr); }
break;
case 70:
#line 252 "../snc.y"
{ yyval.pexpr = expression(E_UNOP, yyvsp[-1].pchar, yyvsp[0].pexpr, 0); }
break;
case 71:
#line 253 "../snc.y"
{ yyval.pexpr = expression(E_PRE, "++", yyvsp[0].pexpr, 0); }
break;
case 72:
#line 254 "../snc.y"
{ yyval.pexpr = expression(E_PRE, "--", yyvsp[0].pexpr, 0); }
break;
case 73:
#line 255 "../snc.y"
{ yyval.pexpr = expression(E_POST, "++", yyvsp[-1].pexpr, 0); }
break;
case 74:
#line 256 "../snc.y"
{ yyval.pexpr = expression(E_POST, "--", yyvsp[-1].pexpr, 0); }
break;
case 75:
#line 257 "../snc.y"
{ yyval.pexpr = expression(E_CONST, yyvsp[0].pchar, 0, 0); }
break;
case 76:
#line 258 "../snc.y"
{ yyval.pexpr = expression(E_CONST, yyvsp[0].pchar, 0, 0); }
break;
case 77:
#line 259 "../snc.y"
{ yyval.pexpr = expression(E_STRING, yyvsp[0].pchar, 0, 0); }
break;
case 78:
#line 260 "../snc.y"
{ yyval.pexpr = expression(E_VAR, yyvsp[0].pchar, 0, 0); }
break;
case 79:
#line 261 "../snc.y"
{ yyval.pexpr = expression(E_FUNC, yyvsp[-3].pchar, yyvsp[-1].pexpr, 0); }
break;
case 80:
#line 262 "../snc.y"
{ yyval.pexpr = expression(E_FUNC, "exit", yyvsp[-1].pexpr, 0); }
break;
case 81:
#line 263 "../snc.y"
{ yyval.pexpr = expression(E_PAREN, "", yyvsp[-1].pexpr, 0); }
break;
case 82:
#line 264 "../snc.y"
{ yyval.pexpr = expression(E_SUBSCR, "", yyvsp[-1].pexpr, yyvsp[0].pexpr); }
break;
case 83:
#line 265 "../snc.y"
{ yyval.pexpr = 0; }
break;
case 84:
#line 269 "../snc.y"
{ yyval.pexpr = link_expr(yyvsp[-2].pexpr, yyvsp[0].pexpr); }
break;
case 85:
#line 270 "../snc.y"
{ yyval.pexpr = link_expr(yyvsp[-2].pexpr, yyvsp[0].pexpr); }
break;
case 86:
#line 274 "../snc.y"
{ yyval.pexpr = yyvsp[-1].pexpr; }
break;
case 87:
#line 278 "../snc.y"
{ yyval.pchar = "+"; }
break;
case 88:
#line 279 "../snc.y"
{ yyval.pchar = "-"; }
break;
case 89:
#line 280 "../snc.y"
{ yyval.pchar = "*"; }
break;
case 90:
#line 281 "../snc.y"
{ yyval.pchar = "&"; }
break;
case 91:
#line 282 "../snc.y"
{ yyval.pchar = "!"; }
break;
case 92:
#line 286 "../snc.y"
{ yyval.pchar = "-"; }
break;
case 93:
#line 287 "../snc.y"
{ yyval.pchar = "+"; }
break;
case 94:
#line 288 "../snc.y"
{ yyval.pchar = "*"; }
break;
case 95:
#line 289 "../snc.y"
{ yyval.pchar = "/"; }
break;
case 96:
#line 290 "../snc.y"
{ yyval.pchar = ">"; }
break;
case 97:
#line 291 "../snc.y"
{ yyval.pchar = ">="; }
break;
case 98:
#line 292 "../snc.y"
{ yyval.pchar = "=="; }
break;
case 99:
#line 293 "../snc.y"
{ yyval.pchar = "!="; }
break;
case 100:
#line 294 "../snc.y"
{ yyval.pchar = "<="; }
break;
case 101:
#line 295 "../snc.y"
{ yyval.pchar = "<"; }
break;
case 102:
#line 296 "../snc.y"
{ yyval.pchar = "||"; }
break;
case 103:
#line 297 "../snc.y"
{ yyval.pchar = "&&"; }
break;
case 104:
#line 298 "../snc.y"
{ yyval.pchar = "<<"; }
break;
case 105:
#line 299 "../snc.y"
{ yyval.pchar = ">>"; }
break;
case 106:
#line 300 "../snc.y"
{ yyval.pchar = "|"; }
break;
case 107:
#line 301 "../snc.y"
{ yyval.pchar = "&"; }
break;
case 108:
#line 302 "../snc.y"
{ yyval.pchar = "^"; }
break;
case 109:
#line 303 "../snc.y"
{ yyval.pchar = "%"; }
break;
case 110:
#line 304 "../snc.y"
{ yyval.pchar = "."; }
break;
case 111:
#line 305 "../snc.y"
{ yyval.pchar = "->"; }
break;
case 112:
#line 309 "../snc.y"
{ yyval.pchar = "="; }
break;
case 113:
#line 310 "../snc.y"
{ yyval.pchar = "+="; }
break;
case 114:
#line 311 "../snc.y"
{ yyval.pchar = "-="; }
break;
case 115:
#line 312 "../snc.y"
{ yyval.pchar = "&="; }
break;
case 116:
#line 313 "../snc.y"
{ yyval.pchar = "|="; }
break;
case 117:
#line 314 "../snc.y"
{ yyval.pchar = "/="; }
break;
case 118:
#line 315 "../snc.y"
{ yyval.pchar = "*="; }
break;
case 119:
#line 316 "../snc.y"
{ yyval.pchar = "%="; }
break;
case 120:
#line 317 "../snc.y"
{ yyval.pchar = "<<="; }
break;
case 121:
#line 318 "../snc.y"
{ yyval.pchar = ">>="; }
break;
case 122:
#line 319 "../snc.y"
{ yyval.pchar = "^="; }
break;
case 123:
#line 323 "../snc.y"
{ yyval.pexpr = expression(E_CMPND, "",yyvsp[-1].pexpr, 0); }
break;
case 124:
#line 324 "../snc.y"
{ snc_err("action statements"); }
break;
case 125:
#line 328 "../snc.y"
{ yyval.pexpr = yyvsp[0].pexpr; }
break;
case 126:
#line 329 "../snc.y"
{ yyval.pexpr = link_expr(yyvsp[-1].pexpr, yyvsp[0].pexpr); }
break;
case 127:
#line 330 "../snc.y"
{ yyval.pexpr = 0; }
break;
case 128:
#line 334 "../snc.y"
{ yyval.pexpr = yyvsp[0].pexpr; }
break;
case 129:
#line 335 "../snc.y"
{ yyval.pexpr = expression(E_STMT, "", yyvsp[-1].pexpr, 0); }
break;
case 130:
#line 336 "../snc.y"
{ yyval.pexpr = expression(E_BREAK, "", 0, 0); }
break;
case 131:
#line 337 "../snc.y"
{ yyval.pexpr = yyvsp[0].pexpr; }
break;
case 132:
#line 338 "../snc.y"
{ yyval.pexpr = yyvsp[0].pexpr; }
break;
case 133:
#line 339 "../snc.y"
{ yyval.pexpr = yyvsp[0].pexpr; }
break;
case 134:
#line 340 "../snc.y"
{ yyval.pexpr = yyvsp[0].pexpr; }
break;
case 135:
#line 341 "../snc.y"
{ yyval.pexpr = expression(E_TEXT, "", yyvsp[0].pchar, 0); }
break;
case 136:
#line 342 "../snc.y"
{ yyval.pexpr = 0; }
break;
case 137:
#line 343 "../snc.y"
{ snc_err("action statement"); }
break;
case 138:
#line 347 "../snc.y"
{ yyval.pexpr = expression(E_IF, "", yyvsp[-2].pexpr, yyvsp[0].pexpr); }
break;
case 139:
#line 351 "../snc.y"
{ yyval.pexpr = expression(E_ELSE, "", yyvsp[0].pexpr, 0); }
break;
case 140:
#line 355 "../snc.y"
{ yyval.pexpr = expression(E_WHILE, "", yyvsp[-2].pexpr, yyvsp[0].pexpr); }
break;
case 141:
#line 360 "../snc.y"
{ yyval.pexpr = expression(E_FOR, "", expression(E_X, "", yyvsp[-6].pexpr, yyvsp[-4].pexpr),
				expression(E_X, "", yyvsp[-2].pexpr, yyvsp[0].pexpr) ); }
break;
case 142:
#line 365 "../snc.y"
{ pp_code(yyvsp[-2].pchar, yyvsp[-1].pchar, ""); }
break;
case 143:
#line 366 "../snc.y"
{ pp_code(yyvsp[-3].pchar, yyvsp[-2].pchar, yyvsp[-1].pchar); }
break;
case 144:
#line 370 "../snc.y"
{ global_c_stmt(yyvsp[0].pexpr); }
break;
case 145:
#line 374 "../snc.y"
{ yyval.pexpr = expression(E_TEXT, "", yyvsp[0].pchar, 0); }
break;
case 146:
#line 375 "../snc.y"
{ yyval.pexpr = link_expr(yyvsp[-1].pexpr, expression(E_TEXT, "", yyvsp[0].pchar, 0)); }
break;
#line 1531 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
