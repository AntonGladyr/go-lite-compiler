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
#include "AST/Statement/TypeDeclarationStatement.hpp"
#include "AST/Statement/DeclarationStatement.hpp"
#include "AST/Statement/AssignStatement.hpp"
#include "AST/Statement/ExpressionStatement.hpp"
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
	std::cerr << "Error: (line " << yylineno << ") " << s << std::endl;
	delete program;
	program = NULL;
	std::exit(EXIT_FAILURE);
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
	#include "AST/Statement/ExpressionStatement.hpp"
	#include "AST/Statement/IfElseStatement.hpp"
	#include "AST/Statement/IncDecStatement.hpp"
	#include "AST/Statement/PrintStatement.hpp"
	#include "AST/Statement/SwitchStatement.hpp"
	#include "AST/Statement/CaseClause.hpp"
	#include "AST/Statement/ReturnStatement.hpp"
	#include "AST/Statement/EmptyStatement.hpp"
	#include "AST/Declaration/FunctionParameter.hpp"
	#include "AST/Declaration/TypeName.hpp"
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
	IdentifierExp *idExp;
	IntegerExp *intExp;
	FloatExp *floatExp;
	StringExp *stringExp;
	BoolExp *boolExp;
	RuneExp *runeExp;

	BlockStatement *blockStmt;	
	std::vector<Statement*> *stmtList;
	ForStatement *forStmt;
	AssignStatement *assignStmt;	
	IfElseStatement *ifElseStmt;
	IncDecStatement *incDecStmt;
	PrintStatement *printStmt;
	SwitchStatement *switchStmt;	
	CaseClause *caseClause;
	std::vector<CaseClause*> *caseBlock;
	EmptyStatement *emptyStmt;
		
	TypeName *type;
	std::vector<IdentifierExp*> *id_list;
    	std::vector<Expression*> *exp_list;	
	FunctionParameter *param;
	std::vector<FunctionParameter*> *params_list;
}

/* Token directives define the token types to be returned by the scanner (excluding character
 * tokens). Each token definition takes [optionally, a reference to the associated field in the
 * yylval union] and an identifier. Multiple tokens can eb defined per directive by using a list
 * of identifiers separated by spaces.
 */

%type <program> program
%type <declList> decl_list
%type <decl> decl var_decl func_decl type_decl
%type <stmt> stmt ifstmt loopstmt assignstmt stmt_decl incdecstmt printstmt returnstmt switchstmt simplestmt emptystmt
%type <blockStmt> blockstmt
%type <exp> exp primary_exp func_call expstmt
%type <param> param
%type <caseBlock> case_block
%type <caseClause> case_clause default_clause

%type <idExp> id_exp
%type <type> type
%type <id_list> id_listne
%type <exp_list> exp_list exp_listpe index
%type <params_list> paramspe paramsne
%type <stmtList> stmt_list switch_stmts

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

program : tPACKAGE tIDENTIFIER tSEMICOLON decl_list { program = new Program(new IdentifierExp(*$2, yylineno), $4, yylineno); delete $2; }
    | tPACKAGE tIDENTIFIER tSEMICOLON { 
	program = new Program(new IdentifierExp(*$2, yylineno), new std::vector<Declaration*>(), yylineno); delete $2; }
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

type_decl : tTYPE tIDENTIFIER type { $$ = new TypeDeclaration(new IdentifierExp(*$2, yylineno), $3, yylineno); delete $2; }
    ;

func_decl : tFUNC tIDENTIFIER tLPAREN paramspe tRPAREN blockstmt
	{ $$ = new FunctionDeclaration(new IdentifierExp(*$2, yylineno), $4, $6, yylineno); delete $2; }
    | tFUNC tIDENTIFIER tLPAREN paramspe tRPAREN type blockstmt
	{ $$ = new FunctionDeclaration(new IdentifierExp(*$2, yylineno), $4, $6, $7, yylineno); delete $2; }
    ;

stmt_list : stmt { $$ = new std::vector<Statement*>(); $$->push_back($1); }
    | stmt_list stmt { $1->push_back($2); }
    ;
   
type : tIDENTIFIER { $$ = new TypeName(*$1, NULL, yylineno); delete $1; } 
    | tLBRACKET tINTVAL tRBRACKET type {
	$$ = new TypeName($4->name, new std::vector<int>(), yylineno); 
	$$->indexes->push_back($2);	
	if ($4->indexes) { $$->indexes->insert($$->indexes->end(), $4->indexes->begin(), $4->indexes->end()); }	
    }
    | tLPAREN type tRPAREN { $$ = $2; }
    ;

id_listne : id_exp { $$ = new std::vector<IdentifierExp*>(); $$->push_back($1); }
    | id_listne tCOMMA id_exp { $1->push_back($3); }
    ;

exp_list : exp { $$ = new std::vector<Expression*>(); $$->push_back($1); }
    | exp_list tCOMMA exp { $1->push_back($3); }
    ;

exp_listpe : exp_list { $$ = $1; }
    | %empty { $$ = new std::vector<Expression*>(); }
    ;

param : tIDENTIFIER type { $$ = new FunctionParameter(new IdentifierExp(*$1, yylineno), $2, yylineno); delete $1; }
    ;

paramsne : param { $$ = new std::vector<FunctionParameter*>(); $$->push_back($1); }
    | paramsne tCOMMA param { $1->push_back($3); }
    ;

paramspe : paramsne 
    | %empty { $$ = NULL; }
    ;

stmt : blockstmt tSEMICOLON { $$ = $1; }
    | stmt_decl tSEMICOLON { $$ = $1; }
    | loopstmt tSEMICOLON { $$ = $1; }
    | ifstmt tSEMICOLON { $$ = $1; }
    | switchstmt tSEMICOLON { $$ = $1; } 
    | printstmt tSEMICOLON { $$ = $1; }
    | returnstmt tSEMICOLON { $$ = $1; }
    | tBREAK tSEMICOLON { $$ = new BreakStatement(yylineno); }
    | tCONTINUE tSEMICOLON { $$ = new ContinueStatement(yylineno); } 
    | simplestmt tSEMICOLON { $$ = $1; }
    ;

emptystmt : %empty { }
    ;

expstmt : exp { $$ = $1; }
    | %empty { $$ = NULL; } 
    ;

stmt_decl : var_decl { $$ = new DeclarationStatement((VariableDeclaration*)$1, yylineno); }
    | type_decl { $$ = new TypeDeclarationStatement((TypeDeclaration*)$1, yylineno); }
    ;

returnstmt : tRETURN { $$ = new ReturnStatement(yylineno); }
    | tRETURN exp { $$ = new ReturnStatement($2, yylineno); } 
    ;

loopstmt : tFOR simplestmt tSEMICOLON expstmt tSEMICOLON simplestmt blockstmt
	{ //TODO: implement short decalration 
	  $$ = new ForStatement($2, $4, $6, $7, yylineno); }
    | tFOR expstmt blockstmt { $$ = new ForStatement($2, $3, yylineno); } 
    ;

simplestmt : emptystmt { $$ = new EmptyStatement(yylineno); }
    | exp { $$ = new ExpressionStatement($1, yylineno); }
    | incdecstmt { $$ = $1; }
    | assignstmt { $$ = $1; }
    ;

assignstmt : exp_list tASSIGN exp_list { $$ = new AssignStatement($1, $3, yylineno); } 
    ;

ifstmt : tIF exp blockstmt { $$ = new IfElseStatement($2, $3, yylineno); }
    | tIF exp blockstmt tELSE blockstmt { $$ = new IfElseStatement($2, $3, $5, yylineno); }
    | tIF exp blockstmt tELSE ifstmt { $$ = new IfElseStatement($2, $3, $5, yylineno); }
    ;

switchstmt : tSWITCH tLBRACE case_block tRBRACE { $$ = new SwitchStatement(NULL, $3, yylineno); }
    | tSWITCH exp tLBRACE case_block tRBRACE { $$ = new SwitchStatement($2, $4, yylineno); }
    ;

case_block : default_clause 
	{ $$ = new std::vector<CaseClause*>(); $$->push_back($1); }
    | case_clause case_block
	{ $$ = new std::vector<CaseClause*>(); $$->push_back($1);	
	  if ($2) $$->insert($$->end(), $2->begin(), $2->end()); } 
    | %empty { $$ = NULL; }
    ;

switch_stmts : stmt_list
    | %empty { $$ = NULL; } 
    ;

case_clause : tCASE exp_list tCOLON switch_stmts 
	{ $$ = new CaseClause($2, new BlockStatement($4, yylineno), SWITCH_CLAUSE::CASE, yylineno);
	 /*$$ = new case_clause(); $$->first = $2; $$->second = new BlockStatement($4, yylineno);*/ }
    ; 

default_clause : tDEFAULT tCOLON switch_stmts
	{ $$ = new CaseClause(NULL, new BlockStatement($3, yylineno), SWITCH_CLAUSE::DEFAULT, yylineno);
	/*$$ = new case_clause(); $$->first = NULL; $$->second = new BlockStatement($3, yylineno);*/ }
    ;

incdecstmt : exp tINC { $$ = new IncDecStatement($1, INC_DEC_OP::INC, yylineno); } 
    | exp tDEC { $$ = new IncDecStatement($1, INC_DEC_OP::DEC, yylineno); }
    ;

printstmt : tPRINT tLPAREN exp_listpe tRPAREN { $$ = new PrintStatement($3, yylineno); }
    | tPRINTLN tLPAREN exp_listpe tRPAREN { $$ = new PrintStatement($3, true, yylineno); }
    ;

blockstmt: tLBRACE stmt_list tRBRACE { $$ = new BlockStatement($2, yylineno); }
    | tLBRACE tRBRACE { $$ = new BlockStatement(new std::vector<Statement*>(), yylineno); } 
    ;

func_call : id_exp tLPAREN exp_listpe tRPAREN { $$ = new FunctionCallExp($1, $3, yylineno); }
    ;

index : tLBRACKET exp tRBRACKET { $$ = new std::vector<Expression*>(); $$->push_back($2); }
    | tLBRACKET exp tRBRACKET index { $$ = new std::vector<Expression*>(); $$->push_back($2); 
				      $$->insert($$->end(), $4->begin(), $4->end()); }
    ;

primary_exp : id_exp { $$ = $1; } 
    |  func_call { $$ = $1; }
    | id_exp index { $$ = new ArrayExp($1, $2, yylineno); }
    | tLPAREN exp tRPAREN { $$ = $2; }
    ;

id_exp : tIDENTIFIER { $$ = new IdentifierExp(*$1, yylineno); delete $1; }
    ;

exp : primary_exp { $$ = $1; }  
    | tLEN tLPAREN exp tRPAREN { $$ = new BuiltinsExp(BUILTIN_LEN, $3, yylineno); }
    | tCAP tLPAREN exp tRPAREN { $$ = new BuiltinsExp(BUILTIN_CAP, $3, yylineno); }
    | exp tPLUS exp { $$ = new BinaryOperatorExp(BINARY_PLUS, $1, $3, yylineno); }
    | exp tMINUS exp { $$ = new BinaryOperatorExp(BINARY_MINUS, $1, $3, yylineno); }
    | exp tTIMES exp { $$ = new BinaryOperatorExp(BINARY_TIMES, $1, $3, yylineno); }
    | exp tDIV exp { $$ = new BinaryOperatorExp(BINARY_DIV, $1, $3, yylineno); }
    | exp tREM exp { $$ = new BinaryOperatorExp(BINARY_REMAIN, $1, $3, yylineno); }
    | exp tBWAND exp { $$ = new BinaryOperatorExp(BINARY_BWAND, $1, $3, yylineno); }
    | exp tBWOR exp { $$ = new BinaryOperatorExp(BINARY_BWOR, $1, $3, yylineno); }
    | exp tBWXOR exp { $$ = new BinaryOperatorExp(BINARY_BWXOR, $1, $3, yylineno); }
    | exp tLEFTSHIFT exp { $$ = new BinaryOperatorExp(BINARY_LEFTSHIFT, $1, $3, yylineno); }
    | exp tRIGHTSHIFT exp { $$ = new BinaryOperatorExp(BINARY_RIGHTSHIFT, $1, $3, yylineno); }
    | exp tBWANDNOT exp { $$ = new BinaryOperatorExp(BINARY_BWANDNOT, $1, $3, yylineno); }
    | exp tAND exp { $$ = new BinaryOperatorExp(BINARY_AND, $1, $3, yylineno); }
    | exp tOR exp { $$ = new BinaryOperatorExp(BINARY_OR, $1, $3, yylineno); }
    | exp tEQUAL exp { $$ = new BinaryOperatorExp(BINARY_EQUAL, $1, $3, yylineno); }
    | exp tNOTEQ exp { $$ = new BinaryOperatorExp(BINARY_NOTEQ, $1, $3, yylineno); }
    | exp tGREATER exp { $$ = new BinaryOperatorExp(BINARY_GREATER, $1, $3, yylineno); }
    | exp tLESS exp { $$ = new BinaryOperatorExp(BINARY_LESS, $1, $3, yylineno); }
    | exp tGREATEREQ exp { $$ = new BinaryOperatorExp(BINARY_GREATEREQ, $1, $3, yylineno); }
    | exp tLESSEQ exp { $$ = new BinaryOperatorExp(BINARY_LESSEQ, $1, $3, yylineno); }
    | tINTVAL { $$ = new IntegerExp($1, yylineno); }
    | tFLOATVAL { $$ = new FloatExp($1, yylineno); }
    | tRUNEVAL { $$ = new RuneExp(*$1, yylineno); delete $1; }
    | tSTRINGVAL { $$ = new StringExp(*$1, yylineno); delete $1; }
    | tBOOLVAL { $$ = new BoolExp($1, yylineno); } 
    | tBANG exp %prec pBANG { $$ = new UnaryExp(UNARY_BANG, $2, yylineno); }
    | tMINUS exp %prec pMINUS { $$ = new UnaryExp(UNARY_MINUS, $2, yylineno); }
    | tPLUS exp %prec pPLUS { $$ = new UnaryExp(UNARY_PLUS, $2, yylineno); }
    | tBWXOR exp %prec pBWXOR { $$ = new UnaryExp(UNARY_BWXOR, $2, yylineno); } 
    ;
%%
