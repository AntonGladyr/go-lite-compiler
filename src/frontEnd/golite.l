%{
#include "GoLite_Parser.hpp" // Token definitions from the parser
#include <string.h>
#include <stdlib.h>
#include <iostream>

// Stores the line number with each token sent to bison
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;

extern int g_tokens;
int insert_semicolon(int token);
using namespace std;
%}

%x COMMENT

/*Helper definitions */
DIGIT [0-9]
ESCAPE [abfnrtv\\'"]

/* Scanner options, line number generation */
%option yylineno
%option noyywrap

/* Removes warnings about input/output functions */
%option noinput
/*%option nounput*/

/* The second section of a flex file contains the regular expressions, using helper definitions
 * where appropriate ({<helper name>}). Sections in flex are divided by %%.
 *
 * Each line contains the regex, followed by the scanner action. Actions are executed when
 * a token is matched. A missing action is treated as a NOP.
 *
 * When building a scanner+parser combo, the parser is responsible for fetching the next token
 * from the scanner, which returns scans and returns a single token at a time. As part of the
 * action, we thus return the next token. Tokens can either be (a) a character; or (b) a token
 * defined in bison (included in y.tab.h).
 */

/* Note the use of 3 keywords:
 *    - yytext: Matched text
 *    - yylineno: Convenience variable for the line number provided by %option yylineno
 *    - yylval: Scanners transform input text into tokens (internally stored as an int) and pass
 *              them to the parser. For some the tokens (identifiers, constants), the original
 *              text is required in later phases. bison provides a variable yylval for each token
 *              to store this extra data. The definition of the yylval struct is provided as
 *              part of the bison grammar file.
 */
%%

[ \t\r]+
"//"([^\n])*

"/*"	BEGIN(COMMENT);
<COMMENT>"/*"	{ fprintf(stderr, "Error: (line %d) Multiple comments opened\n", yylineno); exit(1); }
<COMMENT>"*/"	BEGIN(INITIAL);
<COMMENT><<EOF>> {
	fprintf(stderr, "Error: (line %d) Reached end of file while scanning block comment\n", yylineno); exit(1);
}
<COMMENT>.|"\n"	;

"break"		{ if (g_tokens) cout << "tBREAK" << endl; return insert_semicolon(tBREAK); }
"case"		{ if (g_tokens) cout << "tCASE" << endl; return insert_semicolon(tCASE); }
"chan"		{ if (g_tokens) cout << "tCHAN" << endl; return tCHAN; }
"const" 	{ if (g_tokens) cout << "tCONST" << endl; return tCONST; }
"continue"	{ if (g_tokens) cout << "tCONTINUE" << endl; return tCONTINUE; }
"default"	{ if (g_tokens) cout << "tDEFAULT" << endl; return tDEFAULT; }
"defer"		{ if (g_tokens) cout << "tDEFER" << endl; return tDEFER; }
"else"		{ if (g_tokens) cout << "tELSE" << endl; return tELSE; }
"fallthrough"	{ if (g_tokens) cout << "tFALLTHROUGH" << endl; return insert_semicolon(tFALLTHROUGH); }
"for"		{ if (g_tokens) cout << "tFOR" << endl; return tFOR; }
"func"		{ if (g_tokens) cout << "tFUNC" << endl; return tFUNC; }
"go"		{ if (g_tokens) cout << "tGO" << endl; return tGO; }
"goto"		{ if (g_tokens) cout << "tGOTO" << endl; return tGOTO; }
"if"		{ if (g_tokens) cout << "tIF" << endl; return tIF; }
"import"	{ if (g_tokens) cout << "tIMPORT" << endl; return tIMPORT; }
"interface"	{ if (g_tokens) cout << "tINTERFACE" << endl; return tINTERFACE; }
"map"		{ if (g_tokens) cout << "tMAP" << endl; return tMAP; }
"package"	{ if (g_tokens) cout << "tPACKAGE" << endl; return tPACKAGE; }
"range"		{ if (g_tokens) cout << "tRANGE" << endl; return tRANGE; }
"return"	{ if (g_tokens) cout << "tRETURN" << endl; return insert_semicolon(tRETURN); }
"select"	{ if (g_tokens) cout << "tSELECT" << endl; return tSELECT; }
"struct"	{ if (g_tokens) cout << "tSTRUCT" << endl; return tSTRUCT; }
"switch"	{ if (g_tokens) cout << "tSWITCH" << endl; return tSWITCH; }
"type"		{ if (g_tokens) cout << "tTYPE"; return tTYPE; }
"var"		{ if (g_tokens) cout << "tVAR" << endl; return tVAR; }
"print"		{ if (g_tokens) cout << "tPRINT" << endl; return tPRINT;  }
"println"	{ if (g_tokens) cout << "tPRINTLN"; return tPRINTLN; }
"append"	{ if (g_tokens) cout << "tAPPEND"; return tAPPEND; }
"len"		{ if (g_tokens) cout << "tLEN"; return tLEN; }
"cap"		{ if (g_tokens) cout << "tCAP"; return tCAP; }

"+" 		{ if (g_tokens) cout << "tPLUS" << endl; return tPLUS; }
"-" 		{ if (g_tokens) cout << "tMINUS" << endl; return tMINUS; }
"*" 		{ if (g_tokens) cout << "tTIMES" << endl; return tTIMES; }
"/" 		{ if (g_tokens) cout << "tDIV" << endl; return tDIV; }
"%" 		{ if (g_tokens) cout << "tREM" << endl; return tREM; }

"&" 		{ if (g_tokens) cout << "tBWAND" << endl; return tBWAND; }
"|" 		{ if (g_tokens) cout << "tBWOR" << endl; return tBWOR; }
"^" 		{ if (g_tokens) cout << "tBWXOR" << endl; return tBWXOR; }
"<<" 		{ if (g_tokens) cout << "tLEFTSHIFT" << endl; return tLEFTSHIFT; }
">>" 		{ if (g_tokens) cout << "tRIGHTSHIFT" << endl; return tRIGHTSHIFT; }
"&^" 		{ if (g_tokens) cout << "tBWANDNOT" << endl; return tBWANDNOT; }

"+=" 		{ if (g_tokens) cout << "tPLUSASSIGN" << endl; return tPLUSASSIGN; }
"-=" 		{ if (g_tokens) cout << "tMINUSASSIGN" << endl; return tMINUSASSIGN; }
"*=" 		{ if (g_tokens) cout << "tTIMESASSIGN" << endl; return tTIMESASSIGN; }
"/=" 		{ if (g_tokens) cout << "tDIVASSIGN" << endl; return tDIVASSIGN; }
"%=" 		{ if (g_tokens) cout << "tREMASSIGN" << endl; return tREMASSIGN; }

"&=" 		{ if (g_tokens) cout << "tBWANDASSIGN" << endl; return tBWANDASSIGN; }
"|=" 		{ if (g_tokens) cout << "tBWORASSIGN" << endl; return tBWORASSIGN; }
"^=" 		{ if (g_tokens) cout << "tBWXORASSIGN" << endl; return tBWXORASSIGN; }
"<<=" 		{ if (g_tokens) cout << "tLSHIFTASSIGN" << endl; return tLSHIFTASSIGN; }
">>=" 		{ if (g_tokens) cout << "tRSHIFTASSIGN" << endl; return tRSHIFTASSIGN; }
"&^=" 		{ if (g_tokens) cout << "tBWANDNOTASSIGN" << endl; return tBWANDNOTASSIGN; }

"&&" 		{ if (g_tokens) cout << "tAND" << endl; return tAND; }
"||" 		{ if (g_tokens) cout << "tOR" << endl; return tOR; }
"<-" 		{ if (g_tokens) cout << "tARROW" << endl; return tARROW; }
"++" 		{ if (g_tokens) cout << "tINC" << endl; return insert_semicolon(tINC); }
"--" 		{ if (g_tokens) cout << "tDEC" << endl; return insert_semicolon(tDEC); }

"==" 		{ if (g_tokens) cout << "tEQUAL" << endl;  return tEQUAL; }
"<" 		{ if (g_tokens) cout << "tLESS" << endl; return tLESS; }
">" 		{ if (g_tokens) cout << "tGREATER" << endl; return tGREATER; }
"=" 		{ if (g_tokens) cout << "tASSIGN" << endl; return tASSIGN; }
"!" 		{ if (g_tokens) cout << "tBANG" << endl; return tBANG; }

"!=" 		{ if (g_tokens) cout << "tNOTEQUAL" << endl; return tNOTEQUAL; }
"<=" 		{ if (g_tokens) cout << "tLESSEQUAL" << endl; return tLESSEQUAL; }
">=" 		{ if (g_tokens) cout << "tGREATEREQUAL" << endl; return tGREATEREQUAL; }
":=" 		{ if (g_tokens) cout << "tSHORTDEFINE" << endl; return tSHORTDEFINE; }
"..." 		{ if (g_tokens) cout << "tELLIPSIS" << endl; return tELLIPSIS; }

"(" 		{ if (g_tokens) cout << "tLPAREN" << endl; return tLPAREN; }
"{" 		{ if (g_tokens) cout << "tLBRACE" << endl; return tLBRACE; }
"[" 		{ if (g_tokens) cout << "tLBRACKET" << endl; return tLBRACKET; }
"," 		{ if (g_tokens) cout << "tCOMMA" << endl; return tCOMMA; }
"." 		{ if (g_tokens) cout << "tELLIPSIS" << endl; return tELLIPSIS; }


")" 		{ if (g_tokens) cout << "tRPAREN" << endl; return insert_semicolon(tRPAREN); }
"}" 		{ if (g_tokens) cout << "tRBRACE" << endl; return insert_semicolon(tRBRACE); }
"]" 		{ if (g_tokens) cout << "tRBRACKET" << endl; return insert_semicolon(tRBRACKET); }
";" 		{ if (g_tokens) cout << "tSEMICOLON" << endl; return tSEMICOLON; }

":" 		{ if (g_tokens) cout << "tCOLON" << endl; return tCOLON; }
"_"		{ if (g_tokens) cout << "tBLANKID" << endl; return tBLANKID; }
\n		{ 	int token = insert_semicolon(tNEWLINE);
			if (token != tNEWLINE ) {
				cout << "tSEMICOLON" << endl;
				return token;
			}
		}


([a-zA-Z]|"_")([a-zA-Z]|[0-9]|"_")* { 
    //yylval.identifier = (yytext);
    if (g_tokens) cout << "tIDENTIFIER(" << yytext << ")" << endl;
    return insert_semicolon(tIDENTIFIER);
}

0|([1-9][0-9]*) {
     //yylval.intLiteral = atof(yytext);
    if (g_tokens) cout << "tINTVAL(" << yytext << ")" << endl;
    return insert_semicolon(tINTVAL);
}

0[0-7]* {
    //yylval.intLiteral = atof(yytext);
    if (g_tokens) cout << "tINTVAL(" << yytext << ")" << endl;
    return insert_semicolon(tINTVAL);
}

0(x|X)[0-9a-fA-F][0-9a-fA-F]* {
    //yylval.intLiteral = atof(yytext);
    if (g_tokens) cout << "tINTVAL(" << yytext << ")" << endl;
    return insert_semicolon(tINTVAL);
}

([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*) {
    //yylval.floatLiteral = atof(yytext);
    if (g_tokens) cout << "tFLOATVAL(" << yytext << ")" << endl;
    return insert_semicolon(tFLOATVAL);
}

'((\\[abfnrtv\\\'])|[^\\'])\' {  
	//yylval.rune = (yytext);
	if (g_tokens) cout << "tRUNEVAL(" << yytext << ")" << endl;
	return insert_semicolon(tRUNEVAL);
}

\"([0-9]|[a-zA-Z]|[\t]|\\{ESCAPE})*\" {
    //yylval.string = (yytext);
    if (g_tokens) cout << "tSTRINGVAL(" << yytext << ")" << endl;
    return insert_semicolon(tSTRINGVAL);
}

`(\\.|[^'])*` {
    //yylval.string = (yytext);
    if (g_tokens) cout << "tSTRINGVAL(" << yytext << ")" << endl;
    return insert_semicolon(tSTRINGVAL);
}

. { fprintf(stderr, "Error: (line %d) unexpected character '%s'\n", yylineno, yytext); exit(1); }

%%

int semicolon = 0;

int insert_semicolon(int token) {
	if (semicolon && token == tNEWLINE) {
		unput('\n');
		semicolon = 0;
		return tSEMICOLON;
	} else {
		semicolon = 0;
		semicolon = (	token == tIDENTIFIER || 
				token == tINTVAL || 
				token == tFLOATVAL ||
				token == tRUNEVAL ||
				token == tSTRINGVAL ||
				token == tBREAK ||
				token == tCONTINUE ||
				token == tFALLTHROUGH ||
				token == tRETURN ||
				token == tINC ||
				token == tDEC ||
				token == tRPAREN ||
				token == tRBRACKET ||
				token == tRBRACE
		);
		return token;
	}
}
