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
#include <utility>
#include <string>

using namespace std;

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

    Instruction *ins;
    Declaration *decl;
    Statement *stmt;
    Expression *exp;

    vector<Declaration> *var_list;
    vector<Expression> *exp_list;
    vector<string> *id_list;
    vector<vector<string>> *structdecl_list;
    vector<Pair<Expression, Instruction>> case_list;
    Function *function;
}

/* Token directives define the token types to be returned by the scanner (excluding character
 * tokens). Each token definition takes [optionally, a reference to the associated field in the
 * yylval union] and an identifier. Multiple tokens can eb defined per directive by using a list
 * of identifiers separated by spaces.
 */

%type <ins> program ins
%type <decl> decl varspec shortdecl
%type <stmt> stmt ifstmt loopstmt assignstmt incdecstmt printstmt returnstmt switchstmt
%type <exp> exp

%type <var_list> varspecs
%type <exp_list> exp_list
%type <id_list> id_list 
%type <structdecl_list> structdecl_list
%type <case_list> case_list

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
%token <identifier> tIDENTIFIER
%token tINTVAL
%token tFLOATVAL
%token tBOOLVAL
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

program : tPACKAGE tIDENTIFIER ins { $$ = $3; }
    ;

ins : %empty { $$ = NULL; }
    | decl ins { $$ = new Instruction($1, $2); }
    | stmt ins { $$ = new Instruction($1, $2); }
    | tLPAREN ins tRPAREN ins { $$ = new Instruction($2, $4); }
    ;

decl : tVAR varspec { $$ = $2; }
    | tVAR tLBRACE varspecs tRBRACE { $$ = new Declaration($3); }
    | tFUNC tIDENTIFIER tLBRACE id_list tRBRACE tLPAREN ins tRPAREN { $$ = new Declaration($2, $4, $7); }
    | tFUNC tIDENTIFIER tLBRACE id_list tRBRACE tIDENTIFIER tLPAREN ins returnstmt tRPAREN { $$ = new Declaration($2, $4, $6, $8); }
    | shortdecl { $$ = $1; }
    | tTYPE tIDENTIFIER tIDENTIFIER { $$ = new Declaration($2, $3); }
    | tTYPE tIDENTIFIER tSTRUCT tLPAREN structdecl_list tRPAREN { $$ = new Declaration($2, $5); }
    ;

varspecs : varspec { $$.push_back($1); }
    | varspec tNEWLINE varspecs { $$.push_back($1); $$.push_back($3);}
    ;

varspec : id_list tIDENTIFIER { $$ = new Declaration($1, $2); }
    | id_list tASSIGN exp_list tSEMICOLON {$$ = new Declaration($1, $3); }
    | id_list tIDENTIFIER tASSIGN exp_list tSEMICOLON {$$ = new Declaration($1, $4, $2); }
    ;

shortdecl : tIDENTIFIER tSHORTDECLARE exp tSEMICOLON { $$ = new Declaration($1, $3); }
    ;

id_list : tIDENTIFIER { $$.push_back($1); }
    | tIDENTIFIER tCOMMA id_list { $$.ids.push_back($1); $$.push_back($3); }
    ;

exp_list : %empty { $$ = NULL; }
    | exp { $$.push_back($1); }
    | exp tCOMMA exp_list { $$.push_back($1); $$.push_back($3); }
    ;

structdecl_list : id_list { $$.push_back($1); }
    | id_list tNEWLINE id_list { $$.push_back($1); $$.push_back($3);}
    ;

case_list : %empty { $$ = NULL; }
    | tCASE exp tCOLON ins case_list { $$.emplace_back($2, $4); $$.push_back($5); }
    | tDEFAULT tCOLON ins case_list { $$.emplace_back(NULL, $4); $$.push_back($4); }
    ;

stmt : loopstmt
    | assignstmt
    | ifstmt
    | incdecstmt
    | printstmt
    | returnstmt
    | switchstmt
    | tBREAK tSEMICOLON { $$ = new Statement(k_stmtKindBreak); }
    | tCONTINUE tSEMICOLON { $$ = new Statement(k_stmtKindContinue); }
    ;

returnstmt : tRETURN tSEMICOLON { $$ = new Statement(k_stmtKindReturn); }
    | tRETURN exp tSEMICOLON { $$ = new Statement(k_stmtKindReturn, exp); }
    ;

loopstmt : tFOR ins tSEMICOLON exp tSEMICOLON assignstmt tSEMICOLON tLPAREN ins tRPAREN { $$ = new ForStatement($2, $4, $6, $9); }
    | tFOR exp tLPAREN ins tRPAREN { $$ = new ForStatement($2, $4); }
    | tFOR tLPAREN ins tRPAREN { $$ = new ForStatement($3); }
    ;

assignstmt : id_list tASSIGN exp_list tSEMICOLON { $$ = new AssignStatement($1, $3); }
    | tIDENTIFIER tPERIOD tIDENTIFIER tASSIGN exp tSEMICOLON { $$ = new AssignStatement($1, $3, $5); }
    | tIDENTIFIER tLBRACKET exp tRBRACKET tASSIGN exp tSEMICOLON { $$ = new AssignStatement($1, $3, $6); }
    ;

ifstmt : tIF exp tLPAREN ins tRPAREN { $$ = new IfStatement($2, $4); }
    | tIF shortdecl exp tLPAREN ins tRPAREN { $$ = new IfStatement($3, $5, $2); }
    | tIF exp tLPAREN ins tRPAREN tELSE ifstmt { $$ = new IfElseStatement($2, $4, $7); }
    | tIF shortdecl exp tLPAREN ins tRPAREN tELSE ifstmt { $$ = new IfElseStatement($3, $5, $8, $2); }
    | tIF exp tLPAREN ins tRPAREN tELSE tLPAREN ins tRPAREN { $$ = new IfElseStatement($2, $4, $8); }
    | tIF shortdecl exp tLPAREN ins tRPAREN tELSE tLPAREN ins tRPAREN { $$ = new IfElseStatement($3, $5, $9, $2); }
    ;

incdecstmt : tIDENTIFIER tINC tSEMICOLON { $$ = new Statement(k_stmtKindInc, 1); }
    | tIDENTIFIER tDEC tSEMICOLON { $$ = new Statement(k_stmtKindDec, 1); }
    | tIDENTIFIER tPLUSASSIGN exp tSEMICOLON { $$ = new Statement(k_stmtKindInc, $3); }
    | tIDENTIFIER tMINUSASSIGN exp tSEMICOLON { $$ = new Statemenent(k_stmtKindDec, $3); }
    ;

printstmt : tPRINT tLBRACE exp_list tRBRACE { $$ = new Statement(k_stmtKindPrint, $3, false); }
    | tPRINTLN tLBRACE exp_list tRBRACE { $$ = new Statement(k_stmtKindPrint, $3, true); }
    ;

switchstmt : tSWITCH tLPAREN case_list tRPAREN { $$ = new Statement(k_stmtKindSwitch, $3); }
    | tSWITCH exp tLPAREN case_list tRPAREN { $$ = new Statement(k_stmtKindSwitch, $2, $4); }
    | tSWITCH shortdecl exp tLPAREN case_list tRPAREN { $$ = new Statement(k_stmtKindSwitch, $3, $5, $2); }
    ;

exp : tIDENTIFIER { $$ = new Expression(k_exprKindIdentifier, $1); }
    | tIDENTIFIER tPERIOD tIDENTIFIER { $$ = new Expression(k_exprKindFieldSelector, $1, $3); }
    | tIDENTIFIER tLBRACKET exp tRBRACKET { $$ = new Expression(k_exprKindIndexer, $1, $3); }
    | tIDENTIFIER tLBRACE id_list tRBRACE { $$ = new Expression(k_exprKindFunctionCall, $1, $3); }
    | tAPPEND tLBRACE exp tCOMMA exp tRBRACE { $$ = new Expression(k_exprKindAppend, $3, $5); }
    | tLEN tLBRACE exp tRBRACE { $$ = new Expression(k_exprKindLen, $3); }
    | tCAP tLBRACE exp tRBRACE { $$ = new Expression(k_exprKindCap, $3); }
    ;

%%
