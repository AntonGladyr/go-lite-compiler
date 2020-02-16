/* The first section of a bison file contains:
 *    1. A code section for includes and other arbitrary C code. Copied to the parser verbatim
 *    2. Definition of the yylval union
 *    3. Definition of the tokens
 *    4. Precedence directives
 *    5. The start token
 *    6. Parser options
 */

/* Code section */
%{
#include <stdio.h>
#include <stdlib.h>

// Reference to the line number generated by the scanner
extern int yylineno;
// Reference to the yylex function to quiet a compiler warning
int yylex();

// The yyerror function is called on any syntax error. When using %error-verbose, this function
// takes a single argument (a string) which contains a detailed explanation of the error.
// Otherwise it takes no arguments and it is up to the user to format the error using a minimal
// description provided in yytext.
void yyerror(const char *s) {
	fprintf(stderr, "Error: (line %d) %s\n", yylineno, s);
	exit(1);
}
%}


/* The union directive defines the yylval union used for associating (a) terminals (tokens)
 * returned by flex with additional scanning data (such as identifier/constant values); and
 * optionally (b) non-terminals (variables in productions) with AST information if any.
 */
%union {
	int intval;
	char *identifier;

    Function *function;
}

/* Token directives define the token types to be returned by the scanner (excluding character
 * tokens). Each token definition takes [optionally, a reference to the associated field in the
 * yylval union] and an identifier. Multiple tokens can eb defined per directive by using a list
 * of identifiers separated by spaces.
 */

/*

%token tBREAK
%token tCASE
%token tCHAN
%token tCONST
%token tCONTINUE
%token tDEFAULT
%token tDEFER
%token tELSE
%token tFALLTHROUGH
%token tFOR
%token tFUNC
%token tGO
%token tGOTO
%token tIF
%token tIMPORT
%token tINTERFACE
%token tMAP
%token tPACKAGE
%token tRANGE
%token tRETURN
%token tSELECT
%token tSTRUCT
%token tSWITCH
%token tTYPE
%token tVAR
%token tPRINT
%token tPRINTLN
%token tAPPEND
%token tLEN
%token tCAP
%token tPLUS
%token tMINUS
%token tDIV
%token tTIMES
%token tREM
%token tBWAND
%token tBWOR
%token tBWXOR
%token tRIGHTSHIFT
%token tLEFTSHIFT
%token tBWANDNOT
%token tPLUSASSIGN
%token tMINUSASSIGN
%token tMULTASSIGN
%token tDIVASSIGN
%token tREMASSIGN
%token tBWANDASSIGN
%token tBWORASSIGN
%token tBWXORASSIGN
%token tRSHIFTASSIGN
%token tLSHIFTASSIGN
%token tBWANDNOTASSIGN
%token tAND
%token tOR
%token tARROW
%token tINC
%token tDEC
%token tEQUAL
%token tLESS
%token tGREATER
%token tASSIGN
%token tBANG
%token tNOTEQ
%token tLESSEQ
%token tGREATEREQ
%token tSHORTDECLARE
%token tELLIPSIS
%token tLBRACE
%token tLPAREN
%token tLBRACKET
%token tCOMMA
%token tPERIOD
%token tRBRACE
%token tRPAREN
%token tRBRACKET
%token tSEMICOLON
%token tCOLON
%token tIDENTIFIER
%token tINTVAL
%token tFLOATVAL
%token tRUNEVAL
%token tSTRINGVAL
%token tNEWLINE

/* Precedence directives resolve grammar ambiguities by breaking ties between shift/reduce
 * operations. Tokens are grouped into precendence levels, with lower precedence coming first
 * and then higher precedence in later directives. Tokens specified in the same directive have
 * the same precedence. Ties at the same level are broken using either %left or %right, which
 * denote left-associative and right-associative respectively.
 */
%left '+' '-'
%left '*' '/'

/* Start token (by default if this is missing it takes the first production */
%start program

/* Generate the yylloc structure used for storing line numbers with tokens */
%locations
/* Generate detailed error messages */
%error-verbose

/* The second section of a bison file contains the productions. Note that rules with the
 * same LHS may be joined together and separated with a pipe.
 */
 //todo: unary binary literals expressions,
%% 

program : ins 
    ;

inss : ins inss
    | tLPAREN inss tRPAREN
    ;

ins : 
    | dec 
    | stmt
    ;

dec : tVAR varspec
    | tVAR tLBRACE varspecs tRBRACE
    | tCONST tIDENTIFIER tASSIGN exp tSEMICOLON
    | tFUNC tIDENTIFIER tBRACE var_list tRBRACE vartype tLPAREN inss returnstmt tRPAREN
    | shortdec
    | tTYPE tIDENTIFIER vartype
    | structdec
    ;

varspecs : varspec
    | varspec tCOMMA varspecs
    ;

varspec : var_list vartype
    | var_list tASSIGN multiexp tSEMICOLON
    | var_list tVARTYPE tASSIGN multiexp tSEMICOLON

shortdec : tIDENTIFIER tSHORTASSIGN exp tSEMICOLON
    ;

structdec : tTYPE tIDENTIFIER tSTRUCT tLPAREN structdec_list tRPAREN

global : tPACKAGE tIDENTIFIER
    | tIMPORT tIDENTIFIER
    | tIMPORT tLBRACE multiexp tRBRACE
    ;

var_list : tIDENTIFIER 
    | tIDENTIFIER tCOMMA var_list
    ;

exp_list : 
    | exp
    | exp tCOMMA exp_list
    ;

type_list : vartype
    | vartype tCOMMA type_list
    ;

structdec_list : var_list 
    ;

case_list : tCASE exp tCOLON inss case_list
    | default tCOLON inss case_list
    ;

namedexp_list : tIDENTIFIER tCOLON exp
    | tIDENTIFIER tCOLON exp tCOMMA tNEWLINE namedexp_list
    ;

stmt : loopstmt
    | assignstmt
    | ifstmt
    | incdecstmt
    | printstmt
    | returnstmt
    | switchstmt
    | tBREAK tCOMMA
    | tCONTINUE tCOMMA
    ;

returnstmt : tRETURN
    | tRETURN exp
    ;

loopstmt : tFOR ins tSEMICOLON exp tSEMICOLON assignstmt tSEMICOLON tLPAREN inss tRPAREN
    | tFOR exp tLPAREN inss tRPAREN
    | tFOR LPAREN inss tRPAREN
    ;

assignstmt : 
    | var_list tASSIGN exp_list tSEMICOLON
    | tIDENTIFIER tPERIOD tIDENTIFIER tASSIGN exp tSEMICOLON
    | tIDENTIFIER tLBRACKET exp tRBRACKET tASSIGN exp tSEMICOLON
    ;

ifstmt : tIF exp tLPAREN inss tRPAREN
    | tIF shortdec exp tLPAREN inss tRPAREN
    | tIF exp tLPAREN inss tRPAREN tELSE ifstmt
    | tIF shortdec exp tLPAREN inss tRPAREN tELSE ifstmt
    | tIF exp tLPAREN inss tRPAREN tELSE tLPAREN inss tRPAREN
    | tIF shortdec exp tLPAREN inss tRPAREN tELSE tLPAREN inss tRPAREN
    ;

incdecstmt : tIDENTIFIER tPLUSPLUS
    | tIDENTIFIER tMINUSMINUS
    | tIDENTIFIER tPLUSASSIGN exp
    | tIDENTIFIER tMINUSASSIGN exp
    ;

printstmt : tPRINT tLBRACE exp_list tRBRACE
    | tPRINTLN tLBRACE exp_list tRBRACE
    ;

switchstmt : tSWITCH tLPAREN case_list tRPAREN
    | tSWITCH shortdec exp tLPAREN case_list tRPAREN
    | tSWITCH exp tLPAREN case_list tRPAREN
    ;

exp : tIDENTIFIER
    | tIDENTIFIER tPERIOD tIDENTIFIER
    | tIDENTIFIER tLBRACKET exp tRBRACKET
    | tIDENTIFIER tLBRACE var_list tRBRACE tSEMICOLON
    | tVARTYPE tLBRACE exp tRBRACE tSEMICOLON
    | tIDENTIFIER tLPAREN exp_list tRPAREN
    | tIDENTIFIER tLPAREN namedexp_list tRPAREN
    | tAPPEND tLBRACE exp tCOMMA exp tRBRACE tSEMICOLON
    | tLEN tLBRACE exp tRBRACE tSEMICOLON
    | tCAP tLBRACE exp tRBRACE tSEMICOLON
    ;

vartype : tINT
    | tFLOAT64
    | tBOOL
    | tRUNE
    | tSTRING
    | tLBRACKET exp tRBRACKET tIDENTIFIER
    ;
%%
