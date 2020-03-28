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
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <string>
#include <vector>
#include <memory>
#include "AST/Program/Program.hpp"
#include "AST/Declaration/Declaration.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Statement/ForStatement.hpp"
#include "AST/Statement/AssignStatement.hpp"
#include "AST/Statement/IfStatement.hpp"
#include "AST/Statement/IfElseStatement.hpp"
#include "AST/Statement/IncDecStatement.hpp"
#include "AST/Statement/PrintStatement.hpp"
#include "AST/Statement/SwitchStatement.hpp"
#include "AST/Expression/IdentifierExp.hpp"
#include "AST/Expression/IntegerExp.hpp"
#include "AST/Expression/FloatExp.hpp"
#include "AST/Expression/StringExp.hpp"
#include "AST/Expression/BoolExp.hpp"
#include "AST/Expression/RuneExp.hpp"
#include "AST/Expression/BinaryOperatorExp.hpp"
#include "AST/Expression/UnaryExp.hpp"
#include "AST/Expression/BuiltinsExp.hpp"
#include "AST/Expression/FunctionCallExp.hpp"
#include "AST/Expression/ArrayExp.hpp"


extern Program *program;
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
	#include "AST/Program/Program.hpp"
	#include "AST/Declaration/Declaration.hpp"
	#include "AST/Declaration/VariableDeclaration.hpp"
	#include "AST/Declaration/FunctionDeclaration.hpp"
	#include "AST/Declaration/TypeDeclaration.hpp"
	#include "AST/Statement/Statement.hpp"	
	#include "AST/Expression/Expression.hpp"
	#include "AST/Expression/IdentifierExp.hpp"
	#include "AST/Expression/IntegerExp.hpp"
	#include "AST/Expression/FloatExp.hpp"
	#include "AST/Expression/StringExp.hpp"
	#include "AST/Expression/BoolExp.hpp"
	#include "AST/Expression/RuneExp.hpp"

	#include "AST/Statement/BlockStatement.hpp"
	#include "AST/Statement/ForStatement.hpp"
	#include "AST/Statement/AssignStatement.hpp"
	#include "AST/Statement/IfStatement.hpp"
	#include "AST/Statement/IfElseStatement.hpp"
	#include "AST/Statement/IncDecStatement.hpp"
	#include "AST/Statement/PrintStatement.hpp"
	#include "AST/Statement/SwitchStatement.hpp"
	#include "AST/Statement/ReturnStatement.hpp"
	#include "AST/Statement/EmptyStatement.hpp"
	#include <vector>
        #include <string>
	#include <memory>	
}


/* The union directive defines the yylval union used for associating (a) terminals (tokens)
 * returned by flex with additional scanning data (such as identifier/constant values); and
 * optionally (b) non-terminals (variables in productions) with AST information if any.
 */
%union {
	int intval;
        std::string *identifier;
    	float floatval;
    	std::string *runeval;
    	bool boolval;
    	std::string *stringval;
	char charval;
	
	//std::vector<std::shared_ptr<Declaration>> *declList;
	Program *program;

	std::vector<Declaration*> *declList;	
	VariableDeclaration *varDecl;
	FunctionDeclaration *funcDecl;
	TypeDeclaration *typeDecl;		
	
	Declaration *decl;
	Statement *stmt;
	Expression *exp;
	IntegerExp *intExp;
	FloatExp *floatExp;
	StringExp *stringExp;
	BoolExp *boolExp;
	RuneExp *runeExp;

	BlockStatement *blockStmt;	
	std::vector<Statement*> *stmtList;
	ForStatement *forStmt;
	AssignStatement *assignStmt;
	IfStatement *ifStmt;
	IfElseStatement *ifElseStmt;
	IncDecStatement *incDecStmt;
	PrintStatement *printStmt;
	SwitchStatement *switchStmt;
	EmptyStatement *emptyStmt;
		
	std::pair<std::string, std::vector<int>*> *type;
	std::vector<IdentifierExp*> *id_list;
    	std::vector<Expression*> *exp_list;
    	//std::vector<std::pair<Expression*, Instruction*>> *case_list;
	param_type *param;
	std::vector<param_type*> *params_list;
}

/* Token directives define the token types to be returned by the scanner (excluding character
 * tokens). Each token definition takes [optionally, a reference to the associated field in the
 * yylval union] and an identifier. Multiple tokens can eb defined per directive by using a list
 * of identifiers separated by spaces.
 */

%type <program> program
%type <declList> decl_list
%type <decl> decl var_decl func_decl type_decl
%type <stmt> stmt ifstmt loopstmt assignstmt incdecstmt printstmt returnstmt switchstmt simplestmt emptystmt
%type <blockStmt> blockstmt
%type <exp> exp primary_exp func_call
%type <param> param

%type <type> type
%type <id_list> id_listne
%type <exp_list> exp_list exp_listpe index
%type <params_list> paramspe paramsne
%type <stmtList> stmt_list

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
%token<charval> tLPAREN
%token<charval> tLBRACKET
%token<charval> tCOMMA
%token<charval> tPERIOD
%token tRBRACE
%token<charval> tRPAREN
%token<charval> tRBRACKET
%token tSEMICOLON
%token tCOLON
%token<identifier> tIDENTIFIER
%token<intval> tINTVAL
%token<floatval> tFLOATVAL
%token<boolval> tBOOLVAL
%token<runeval> tRUNEVAL
%token<stringval> tSTRINGVAL
%token tNEWLINE

/* Precedence directives resolve grammar ambiguities by breaking ties between shift/reduce
 * operations. Tokens are grouped into precendence levels, with lower precedence coming first
 * and then higher precedence in later directives. Tokens specified in the same directive have
 * the same precedence. Ties at the same level are broken using either %left or %right, which
 * denote left-associative and right-associative respectively.
 */

%left tPLUS tMINUS tBWOR tBWXOR
%left tTIMES tDIV tREM tBWAND tBWANDNOT tLEFTSHIFT tRIGHTSHIFT
%left tEQUAL tNOTEQ tLESS tLESSEQ tGREATER tGREATEREQ
%left tAND
%left tOR
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
%%

program : tPACKAGE tIDENTIFIER tSEMICOLON decl_list { program = new Program(*$2, $4, yylineno); delete $2; }
    | tPACKAGE tIDENTIFIER tSEMICOLON { program = new Program(*$2, new std::vector<Declaration*>(), yylineno); delete $2; }
    ;

decl_list : decl { $$ = new std::vector<Declaration*>(); $$->push_back($1); }
    | decl_list decl { $1->push_back($2); }
    ;

decl : var_decl tSEMICOLON
    | type_decl tSEMICOLON
    | func_decl tSEMICOLON 
    ;

var_decl : tVAR id_listne type { $$ = new VariableDeclaration($2, $3, yylineno); }
    | tVAR id_listne tASSIGN exp_list { $$ = new VariableDeclaration($2, $4, yylineno); }
    | tVAR id_listne type tASSIGN exp_list { $$ = new VariableDeclaration($2, $3, $5, yylineno); }
    ;

type_decl : tTYPE tIDENTIFIER type { $$ = new TypeDeclaration(*$2, $3, yylineno); delete $2; }
    ;

func_decl : tFUNC tIDENTIFIER tLPAREN paramspe tRPAREN blockstmt
	{ $$ = new FunctionDeclaration(*$2, $4, $6, yylineno); delete $2; }
    | tFUNC tIDENTIFIER tLPAREN paramspe tRPAREN type blockstmt
	{ $$ = new FunctionDeclaration(*$2, $4, $6, $7, yylineno); delete $2; }
    ;

stmt_list : stmt { $$ = new std::vector<Statement*>(); $$->push_back($1); }
    | stmt_list stmt { $1->push_back($2); }
    ;
   
type : tIDENTIFIER { $$ = new std::pair<std::string, std::vector<int>*>;  
		     $$->second = new std::vector<int>(); $$->first = *$1; delete $1; }
    | tLBRACKET tINTVAL tRBRACKET type {	
	$$ = new std::pair<std::string, std::vector<int>*>;		
	$$->first = $4->first;  $$->second = new std::vector<int>();
	$$->second->push_back($2);	
	$$->second->insert($$->second->end(), $4->second->begin(), $4->second->end());	
    }
    | tLPAREN type tRPAREN { $$ = new std::pair<std::string, std::vector<int>*>; $$ = $2; }
    ;

id_listne : tIDENTIFIER { $$ = new std::vector<IdentifierExp*>();
			  $$->push_back(new IdentifierExp(*$1, yylineno)); delete $1; }
    | id_listne tCOMMA tIDENTIFIER { $1->push_back(new IdentifierExp(*$3, yylineno)); delete $3; }
    ;

exp_list : exp { $$ = new std::vector<Expression*>(); $$->push_back($1); }
    | exp_list tCOMMA exp { $1->push_back($3); }
    ;

exp_listpe : exp_list { $$ = $1; }
    | %empty { $$ = new std::vector<Expression*>(); }
    ;

param : tIDENTIFIER type { $$ = new param_type(); $$->first = *$1; $$->second = $2; delete $1; }
    ;

paramsne : param { $$ = new std::vector<param_type*>(); $$->push_back($1); }
    | paramsne tCOMMA param { $1->push_back($3); }
    ;

paramspe : paramsne 
    | %empty { $$ = NULL; }
    ;

stmt : blockstmt tSEMICOLON { $$ = $1; }
    | stmt_decl tSEMICOLON { $$ = NULL; }
    | loopstmt tSEMICOLON { $$ = NULL; }
    | ifstmt tSEMICOLON { $$ = NULL; }
    | switchstmt tSEMICOLON { $$ = NULL; }   
    | printstmt tSEMICOLON { $$ = NULL; }
    | returnstmt tSEMICOLON { $$ = $1; }
    | tBREAK tSEMICOLON {/*$$ = new BreakStatement();*/ $$ = NULL; }
    | tCONTINUE tSEMICOLON {/*$$ = new ContinueStatement();*/ $$ = NULL; } 
    | simplestmt tSEMICOLON { $$ = $1; }
    ;

emptystmt : %empty { }
    ;

expstmt : exp { }
    | %empty 
    ;

stmt_decl : var_decl { }
    | type_decl 
    ;

returnstmt : tRETURN { $$ = new ReturnStatement(yylineno); }
    | tRETURN exp { $$ = new ReturnStatement($2, yylineno); } 
    ;

loopstmt : tFOR simplestmt tSEMICOLON expstmt tSEMICOLON simplestmt blockstmt { $$ = NULL; }
    | tFOR exp blockstmt {/*$$ = new ForStatement($2, $4);*/ $$ = NULL; }
    | tFOR blockstmt {/*$$ = new ForStatement($3);*/ $$ = NULL; }
    ;

simplestmt : emptystmt { $$ = new EmptyStatement(yylineno); }
    | exp { }
    | incdecstmt { }
    | assignstmt { }
    ;

assignstmt : exp_list tASSIGN exp_list { } 
    ;

ifstmt : tIF exp blockstmt {/*$$ = new IfStatement($2, $4);*/} 
    | tIF exp blockstmt tELSE blockstmt {/*$$ = new IfElseStatement(k_stmtKindIfElse, $2, $4, $7);*/} 
    | tIF exp blockstmt tELSE ifstmt {/*$$ = new IfElseStatement(k_stmtKindIfElseNested, $2, $4, $8);*/} 
    ;

switchstmt : tSWITCH tLBRACE case_block tRBRACE {/*$$ = new SwitchStatement($3);*/ $$ = NULL; }
    | tSWITCH exp tLBRACE case_block tRBRACE {/*$$ = new SwitchStatement($2, $4);*/ $$ = NULL; }
    ;

case_block : default_clause
    | case_clause case_block
    | %empty 
    ;

switch_stmts : stmt_list
    | %empty   
    ;

case_clause : tCASE exp_list tCOLON switch_stmts  { }
    ; 

default_clause : tDEFAULT tCOLON switch_stmts { }
    ;

incdecstmt : exp tINC {/*$$ = new IncDecStatement(k_stmtKindInc, $$1);*/} 
    | exp tDEC {/*$$ = new IncDecStatement(k_stmtKindDec, $$1);*/}
    ;

printstmt : tPRINT tLPAREN exp_listpe tRPAREN {/*$$ = new PrintStatement(k_stmtKindPrint, $3);*/}
    | tPRINTLN tLPAREN exp_listpe tRPAREN {/*$$ = new PrintStatement(k_stmtKindPrintLn, $3);*/}
    ;

blockstmt: tLBRACE stmt_list tRBRACE { $$ = new BlockStatement($2, yylineno); }
    | tLBRACE tRBRACE { $$ = new BlockStatement(new std::vector<Statement*>(), yylineno); } 
    ;

func_call : primary_exp tLPAREN exp_listpe tRPAREN { $$ = new FunctionCallExp($1, $3, yylineno); }
    ;

index : tLBRACKET exp tRBRACKET { $$ = new std::vector<Expression*>(); $$->push_back($2); }
    | tLBRACKET exp tRBRACKET index { $$ = new std::vector<Expression*>(); $$->push_back($2); 
				      $$->insert($$->end(), $4->begin(), $4->end()); }
    ;

primary_exp : tIDENTIFIER { $$ = new IdentifierExp(*$1, yylineno); delete $1; }
    | func_call { $$ = $1; }
    | tIDENTIFIER index { $$ = new ArrayExp(*$1, $2, yylineno); delete $1; }
    | tLPAREN exp tRPAREN { $$ = $2; }
    ;

exp : primary_exp
    | tLEN tLPAREN exp tRPAREN { $$ = new BuiltinsExp("len", $3, yylineno); }
    | tCAP tLPAREN exp tRPAREN { $$ = new BuiltinsExp("cap", $3, yylineno); }
    | exp tPLUS exp { $$ = new BinaryOperatorExp("+", $1, $3, yylineno); }
    | exp tMINUS exp { $$ = new BinaryOperatorExp("-", $1, $3, yylineno); }
    | exp tTIMES exp { $$ = new BinaryOperatorExp("*", $1, $3, yylineno); }
    | exp tDIV exp { $$ = new BinaryOperatorExp("/", $1, $3, yylineno); }
    | exp tREM exp { $$ = new BinaryOperatorExp("%", $1, $3, yylineno); }
    | exp tBWAND exp { $$ = new BinaryOperatorExp("&", $1, $3, yylineno); }
    | exp tBWOR exp { $$ = new BinaryOperatorExp("|", $1, $3, yylineno); }
    | exp tBWXOR exp { $$ = new BinaryOperatorExp("^", $1, $3, yylineno); }
    | exp tLEFTSHIFT exp { $$ = new BinaryOperatorExp("<<", $1, $3, yylineno); }
    | exp tRIGHTSHIFT exp { $$ = new BinaryOperatorExp(">>", $1, $3, yylineno); }
    | exp tBWANDNOT exp { $$ = new BinaryOperatorExp("&^", $1, $3, yylineno); }
    | exp tAND exp { $$ = new BinaryOperatorExp("&&", $1, $3, yylineno); }
    | exp tOR exp { $$ = new BinaryOperatorExp("||", $1, $3, yylineno); }
    | exp tEQUAL exp { $$ = new BinaryOperatorExp("==", $1, $3, yylineno); }
    | exp tNOTEQ exp { $$ = new BinaryOperatorExp("!=", $1, $3, yylineno); }
    | exp tGREATER exp { $$ = new BinaryOperatorExp(">", $1, $3, yylineno); }
    | exp tLESS exp { $$ = new BinaryOperatorExp("<", $1, $3, yylineno); }
    | exp tGREATEREQ exp { $$ = new BinaryOperatorExp(">=", $1, $3, yylineno); }
    | exp tLESSEQ exp { $$ = new BinaryOperatorExp("<=", $1, $3, yylineno); }
    | tINTVAL { $$ = new IntegerExp($1, yylineno); }
    | tFLOATVAL { $$ = new FloatExp($1, yylineno); }
    | tRUNEVAL { $$ = new RuneExp(*$1, yylineno); delete $1; }
    | tSTRINGVAL { $$ = new StringExp(*$1, yylineno); delete $1; }
    | tBOOLVAL { $$ = new BoolExp($1, yylineno); } 
    | tBANG exp %prec pBANG { $$ = new UnaryExp("!", $2, yylineno); }
    | tMINUS exp %prec pMINUS { $$ = new UnaryExp("-", $2, yylineno); }
    | tPLUS exp %prec pPLUS { $$ = new UnaryExp("+", $2, yylineno); }
    | tBWXOR exp %prec pBWXOR { $$ = new UnaryExp("^", $2, yylineno); } 
    ;
%%
