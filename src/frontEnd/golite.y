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
#include <vector>
#include "tree.h"
#include "Instruction.hpp"
#include "Statement.hpp"
#include "Declaration.hpp"
#include "ForStatement.hpp"
#include "AssignStatement.hpp"
#include "IfStatement.hpp"
#include "IfElseStatement.hpp"
#include "IncDecStatement.hpp"
#include "PrintStatement.hpp"
#include "SwitchStatement.hpp"


extern Instruction *rootIns;
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

%code requires
{	
	#include "Instruction.hpp"
	#include "Declaration.hpp"
	#include "Statement.hpp"
	#include "Expression.hpp"
	#include "ForStatement.hpp"
	#include "AssignStatement.hpp"
	#include "IfStatement.hpp"
	#include "IfElseStatement.hpp"
	#include "IncDecStatement.hpp"
	#include "PrintStatement.hpp"
	#include "SwitchStatement.hpp"
	#include <vector>
}


/* The union directive defines the yylval union used for associating (a) terminals (tokens)
 * returned by flex with additional scanning data (such as identifier/constant values); and
 * optionally (b) non-terminals (variables in productions) with AST information if any.
 */
%union {
	int intval;
	char *identifier;
    	float floatval;
    	char runeval;
    	bool boolval;
    	char *stringval;

    	Instruction *ins;
	Declaration *decl;
	Statement *stmt;
	Expression *exp;
	
	ForStatement *forStmt;
	AssignStatement *assignStmt;
	IfStatement *ifStmt;
	IfElseStatement *ifElseStmt;
	IncDecStatement *incDecStmt;
	PrintStatement *printStmt;
	SwitchStatement *switchStmt;

	std::vector<Declaration*> *var_list;
    	std::vector<Expression*> *exp_list;
    	std::vector<std::string> *id_list;
    	std::vector<std::vector<std::string>> *structdecl_list;
    	std::vector<std::pair<Expression*, Instruction*>> *case_list;
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
%token tCONST
%token tCHAN
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
%token <intval> tINTVAL
%token <floatval> tFLOATVAL
%token <boolval> tBOOLVAL
%token <runeval> tRUNEVAL
%token <stringval> tSTRINGVAL
%token tNEWLINE

/* Precedence directives resolve grammar ambiguities by breaking ties between shift/reduce
 * operations. Tokens are grouped into precendence levels, with lower precedence coming first
 * and then higher precedence in later directives. Tokens specified in the same directive have
 * the same precedence. Ties at the same level are broken using either %left or %right, which
 * denote left-associative and right-associative respectively.
 */
%left '+' '-' 
%left '*' '/'
%left pMINUS pBANG pPLUS pBWXOR


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

program : tPACKAGE tIDENTIFIER ins { /*$$ = $3; */}
    ;

ins : %empty { $$ = NULL; }
    | decl ins {/*$$ = new Instruction($1, $2);*/}
    | stmt ins {/*$$ = new Instruction($1, $2);*/}
    | tLPAREN ins tRPAREN ins {/*$$ = new Instruction($2, $4);*/}
    ;

decl : tVAR varspec { /* TODO: fix //$$ = $2; */}
    | tVAR tLBRACE varspecs tRBRACE { /* TODO: fix //$$ = new Declaration(*$3); delete $3; */ }
    | tFUNC tIDENTIFIER tLBRACE id_list tRBRACE tIDENTIFIER tLPAREN ins returnstmt tRPAREN
	{/*$$ = new FunctionDeclaration($2, *$4, $6, $8);*/}
    | shortdecl {/*$$ = $1;*/}
    | tTYPE tIDENTIFIER tIDENTIFIER { /*$$ = new TypeDeclaration($2, $3);*/ }
    | tTYPE tIDENTIFIER tSTRUCT tLPAREN structdecl_list tRPAREN {/*$$ = new StructDeclaration($2, *$5);*/}
    ;

varspecs : %empty {/*$$ = new std::vector<Declaration*>();*/}
    | varspec {/*$$ = new std::vector<Declaration*>(); $$->push_back($1);*/}
    | varspecs tNEWLINE varspec {/*$1->push_back($3);*/}
    ;

varspec : id_list tIDENTIFIER {/*$$ = new Declaration(*$1, $2);*/}
    | id_list tASSIGN exp_list tSEMICOLON {/*$$ = new Declaration(*$1, *$3);*/}
    | id_list tIDENTIFIER tASSIGN exp_list tSEMICOLON {/*$$ = new Declaration(*$1, *$4, $2);*/}
    ;

shortdecl : tIDENTIFIER tSHORTDECLARE exp tSEMICOLON {/*$$ = new ShortDeclaration($1, $3);*/}
    ;

id_list : tIDENTIFIER {/*$$ = new std::vector<std::string>(); $$->push_back($1);*/}
    | id_list tCOMMA tIDENTIFIER {/*$1->push_back($3);*/}
    ;

exp_list : %empty {/*$$ = new std::vector<Expression*>();*/}
    | exp {/*$$ = new std::vector<Expression*>(); $$->push_back($1);*/}
    | exp_list tCOMMA exp {/*$1->push_back($3);*/}
    ;

structdecl_list : %empty {/*$$ = new std::vector<std::vector<std::string>>();*/}
    | id_list {/*$$ = new std::vector<std::vector<std::string>>(); $$->push_back(*$1);*/}
    | structdecl_list tNEWLINE id_list {/*$1->push_back(*$3);*/}
    ;

case_list : %empty {/*$$ = new std::vector<std::pair<Expression*, Instruction*>>();*/}
    | tCASE exp tCOLON ins case_list {/*$$ = new std::vector<std::pair<Expression*, Instruction*>>(); $$->emplace_back($2, $4);*/}
    | tDEFAULT tCOLON ins case_list {/*$$->emplace_back(NULL, $4);*/}
    ;

stmt : loopstmt
    | assignstmt 
    | ifstmt
    | incdecstmt
    | printstmt
    | returnstmt
    | switchstmt
    | tBREAK tSEMICOLON {/*$$ = new BreakStatement();*/}
    | tCONTINUE tSEMICOLON {/*$$ = new ContinueStatement();*/}
    ;

returnstmt : tRETURN tSEMICOLON {/*&$$ = new ReturnStatement();*/}
    | tRETURN exp tSEMICOLON {/*$$ = new ReturnStatement(exp);*/}
    ;

loopstmt : tFOR ins tSEMICOLON exp tSEMICOLON assignstmt tLBRACE ins tRBRACE {/*$$ = new ForStatement($2, $4, $6, $8);*/}
    | tFOR exp tLBRACE ins tRBRACE {/*$$ = new ForStatement($2, $4);*/}
    | tFOR tLBRACE ins tRBRACE {/*$$ = new ForStatement($3);*/}
    ;

assignstmt : id_list tASSIGN exp_list tSEMICOLON {/*$$ = new AssignStatement($1, $3);*/}
    | tIDENTIFIER tPERIOD tIDENTIFIER tASSIGN exp tSEMICOLON {/*$$ = new AssignStatement($1, $3, $5);*/}
    | tIDENTIFIER tLBRACKET exp tRBRACKET tASSIGN exp tSEMICOLON {/*$$ = new AssignStatement($1, $3, $6);*/}
    ;

ifstmt : tIF exp tLBRACE ins tRBRACE {/*$$ = new IfStatement($2, $4);*/}
    | tIF shortdecl exp tLBRACE ins tRBRACE {/*$$ = new IfStatement($3, $5, $2);*/}
    | tIF exp tLBRACE ins tRBRACE tELSE ifstmt {/*$$ = new IfElseStatement(k_stmtKindIfElse, $2, $4, $7);*/}
    | tIF shortdecl exp tLBRACE ins tRBRACE tELSE ifstmt {/*$$ = new IfElseStatement(k_stmtKindDeclIfElse, $3, $5, $8, $2);*/}
    | tIF exp tLBRACE ins tRBRACE tELSE tLBRACE ins tRBRACE {/*$$ = new IfElseStatement(k_stmtKindIfElseNested, $2, $4, $8);*/}
    | tIF shortdecl exp tLBRACE ins tRBRACE tELSE tLBRACE ins tRBRACE {/*$$ = new IfElseStatement(k_stmtKindDeclIfElseNested, $3, $5, $9, $2);*/}
    ;

incdecstmt : tIDENTIFIER tINC tSEMICOLON {/*$$ = new IncDecStatement(k_stmtKindInc, $$1);*/}
    | tIDENTIFIER tDEC tSEMICOLON {/*$$ = new IncDecStatement(k_stmtKindDec, $$1);*/}
    | tIDENTIFIER tPLUSASSIGN exp tSEMICOLON {/*$$ = new IncDecStatement(k_stmtKindIncExp, $$1, $3);*/}
    | tIDENTIFIER tMINUSASSIGN exp tSEMICOLON {/*$$ = new IncDecStatement(k_stmtKindDecExp, $$1, $3);*/}
    ;

printstmt : tPRINT tLBRACE exp_list tRBRACE {/*$$ = new PrintStatement(k_stmtKindPrint, $3);*/}
    | tPRINTLN tLBRACE exp_list tRBRACE {/*$$ = new PrintStatement(k_stmtKindPrintLn, $3);*/}
    ;

switchstmt : tSWITCH tLBRACE case_list tRBRACE {/*$$ = new SwitchStatement($3);*/}
    | tSWITCH exp tLBRACE case_list tRBRACE {/*$$ = new SwitchStatement($2, $4);*/}
    | tSWITCH shortdecl tLBRACE case_list tRBRACE {/*$$ = new SwitchStatement($2, $4);*/}
    ;

exp : tIDENTIFIER tPERIOD tIDENTIFIER {/*$$ = new Binary(k_exprKindFieldSelector, $1, $3);*/}
    | tIDENTIFIER tLBRACKET exp tRBRACKET {/*$$ = new Binary(k_exprKindIndexer, $1, $3);*/}
    | tIDENTIFIER tLBRACE id_list tRBRACE {/*$$ = new Binary(k_exprKindFunctionCall, $1, $3);*/}
    | tAPPEND tLBRACE exp tCOMMA exp tRBRACE {/*$$ = new Binary(k_exprKindAppend, $3, $5);*/}
    | tLEN tLBRACE exp tRBRACE {/*$$ = new Binary(k_exprKindLen, $3);*/}
    | tCAP tLBRACE exp tRBRACE {/*$$ = new Binary(k_exprKindCap, $3);*/}
    | tPLUS exp %prec pPLUS {/*$$ = new Unary(k_exprKindPlus, $2);*/}
    | tMINUS exp %prec pMINUS {/*$$ = new Unary(k_exprKindMinus, $2);*/}
    | tBANG exp %prec pBANG {/*$$ = new Unary(k_exprKindBang, $2);*/}
    | tBWXOR exp %prec pBWXOR {/*$$ = new Unary(k_exprKindBwxor, $2);*/}
    | tINTVAL {/*$$ = new Literal(k_exprKindInt, $1);*/}
    | tFLOATVAL {/*$$ = new Literal(k_exprKindFloat, $1);*/}
    | tRUNEVAL {/*$$ = new Literal(k_exprKindChar, $1);*/}
    | tSTRINGVAL {/*$$ = new Literal(k_exprKindChar, $1);*/}
    | tBOOLVAL {/*$$ = new Literal(k_exprKindBool, $1);*/}
    | tIDENTIFIER {/*$$ = new Literal(k_exprKindIdentifier, $1);*/}
    ; 

%%
