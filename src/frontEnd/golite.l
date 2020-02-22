%{
#include "GoLite_Parser.hpp" // Token definitions from the parser
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

extern int g_tokens;
// Stores the line number with each token sent to bison
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;

extern int g_tokens;
using namespace std;

int lastToken = -1;
#define RETURN(token) lastToken = token; return token;

int insertSemicolon() {
		return lastToken == tIDENTIFIER ||
			lastToken == tINTVAL ||
			lastToken == tFLOATVAL ||
			lastToken == tRUNEVAL ||
			lastToken == tSTRINGVAL ||
			lastToken == tBREAK ||
			lastToken == tCONTINUE ||
			lastToken == tFALLTHROUGH ||
			lastToken == tRETURN ||
			lastToken == tINC ||
			lastToken == tDEC ||
			lastToken == tRPAREN ||
			lastToken == tRBRACKET ||
			lastToken == tRBRACE
			;
}
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
%option nounput

/* The second section of a flex file contains the regular expressions, using helper definitions
 * where appropriate ({<helper name>}). Sections in flex are divided by %%.
 *
 * Each line contains the regex, followed by the scanner action. Actions are executed when
 * a token is matched. A missing action is treated as a NOP.
 *
 * When building a scanner+parser combo, the parser is responsible for fetching the next token
 * from the scanner, which //returns scans and //returns a single token at a time. As part of the
 * action, we thus //return the next token. Tokens can either be (a) a character; or (b) a token
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

"break"		{ if (g_tokens) cout << "tBREAK" << endl; RETURN(tBREAK); }
"case"		{ if (g_tokens) cout << "tCASE" << endl; RETURN(tCASE); }
"chan"		{ if (g_tokens) cout << "tCHAN" << endl; RETURN(tCHAN); }
"const" 	{ if (g_tokens) cout << "tCONST" << endl; RETURN(tCONST); }
"continue"	{ if (g_tokens) cout << "tCONTINUE" << endl; RETURN(tCONTINUE); }
"default"	{ if (g_tokens) cout << "tDEFAULT" << endl; RETURN(tDEFAULT); }
"defer"		{ if (g_tokens) cout << "tDEFER" << endl; RETURN(tDEFER); }
"else"		{ if (g_tokens) cout << "tELSE" << endl; RETURN(tELSE); }
"fallthrough"	{ if (g_tokens) cout << "tFALLTHROUGH" << endl; RETURN(tFALLTHROUGH); }
"for"		{ if (g_tokens) cout << "tFOR" << endl; RETURN(tFOR); }
"func"		{ if (g_tokens) cout << "tFUNC" << endl; RETURN(tFUNC); }
"go"		{ if (g_tokens) cout << "tGO" << endl; RETURN(tGO); }
"goto"		{ if (g_tokens) cout << "tGOTO" << endl; RETURN(tGOTO); }
"if"		{ if (g_tokens) cout << "tIF" << endl; RETURN(tIF); }
"import"	{ if (g_tokens) cout << "tIMPORT" << endl; RETURN(tIMPORT); }
"interface"	{ if (g_tokens) cout << "tINTERFACE" << endl; RETURN(tINTERFACE); }
"map"		{ if (g_tokens) cout << "tMAP" << endl; RETURN(tMAP); }
"package"	{ if (g_tokens) cout << "tPACKAGE" << endl; RETURN(tPACKAGE); }
"range"		{ if (g_tokens) cout << "tRANGE" << endl; RETURN(tRANGE); }
"return"	{ if (g_tokens) cout << "tRETURN" << endl; RETURN(tRETURN); }
"select"	{ if (g_tokens) cout << "tSELECT" << endl; RETURN(tSELECT); }
"struct"	{ if (g_tokens) cout << "tSTRUCT" << endl; RETURN(tSTRUCT); }
"switch"	{ if (g_tokens) cout << "tSWITCH" << endl; RETURN(tSWITCH); }
"type"		{ if (g_tokens) cout << "tTYPE" << endl; RETURN(tTYPE); }
"var"		{ if (g_tokens) cout << "tVAR" << endl; RETURN(tVAR); }
"print"		{ if (g_tokens) cout << "tPRINT" << endl; RETURN(tPRINT);  }
"println"	{ if (g_tokens) cout << "tPRINTLN" << endl; RETURN(tPRINTLN); }
"append"	{ if (g_tokens) cout << "tAPPEND" << endl; RETURN(tAPPEND); }
"len"		{ if (g_tokens) cout << "tLEN" << endl; RETURN(tLEN); }
"cap"		{ if (g_tokens) cout << "tCAP" << endl; RETURN(tCAP); }

"+" 		{ if (g_tokens) cout << "tPLUS" << endl; RETURN(tPLUS); }
"-" 		{ if (g_tokens) cout << "tMINUS" << endl; RETURN(tMINUS); }
"*" 		{ if (g_tokens) cout << "tTIMES" << endl; RETURN(tTIMES); }
"/" 		{ if (g_tokens) cout << "tDIV" << endl; RETURN(tDIV); }
"%" 		{ if (g_tokens) cout << "tREM" << endl; RETURN(tREM); }

"&" 		{ if (g_tokens) cout << "tBWAND" << endl; RETURN(tBWAND); }
"|" 		{ if (g_tokens) cout << "tBWOR" << endl; RETURN(tBWOR); }
"^" 		{ if (g_tokens) cout << "tBWXOR" << endl; RETURN(tBWXOR); }
"<<" 		{ if (g_tokens) cout << "tLEFTSHIFT" << endl; RETURN(tLEFTSHIFT); }
">>" 		{ if (g_tokens) cout << "tRIGHTSHIFT" << endl; RETURN(tRIGHTSHIFT); }
"&^" 		{ if (g_tokens) cout << "tBWANDNOT" << endl; RETURN(tBWANDNOT); }

"+=" 		{ if (g_tokens) cout << "tPLUSASSIGN" << endl; RETURN(tPLUSASSIGN); }
"-=" 		{ if (g_tokens) cout << "tMINUSASSIGN" << endl; RETURN(tMINUSASSIGN); }
"*=" 		{ if (g_tokens) cout << "tMULTASSIGN" << endl; RETURN(tMULTASSIGN); }
"/=" 		{ if (g_tokens) cout << "tDIVASSIGN" << endl; RETURN(tDIVASSIGN); }
"%=" 		{ if (g_tokens) cout << "tREMASSIGN" << endl; RETURN(tREMASSIGN); }

"&=" 		{ if (g_tokens) cout << "tBWANDASSIGN" << endl; RETURN(tBWANDASSIGN); }
"|=" 		{ if (g_tokens) cout << "tBWORASSIGN" << endl; RETURN(tBWORASSIGN); }
"^=" 		{ if (g_tokens) cout << "tBWXORASSIGN" << endl; RETURN(tBWXORASSIGN); }
"<<=" 		{ if (g_tokens) cout << "tLSHIFTASSIGN" << endl; RETURN(tLSHIFTASSIGN); }
">>=" 		{ if (g_tokens) cout << "tRSHIFTASSIGN" << endl; RETURN(tRSHIFTASSIGN); }
"&^=" 		{ if (g_tokens) cout << "tBWANDNOTASSIGN" << endl; RETURN(tBWANDNOTASSIGN); }

"&&" 		{ if (g_tokens) cout << "tAND" << endl; RETURN(tAND); }
"||" 		{ if (g_tokens) cout << "tOR" << endl; RETURN(tOR); }
"<-" 		{ if (g_tokens) cout << "tARROW" << endl; RETURN(tARROW); }
"++" 		{ if (g_tokens) cout << "tINC" << endl; RETURN(tINC); }
"--" 		{ if (g_tokens) cout << "tDEC" << endl; RETURN(tDEC); }

"==" 		{ if (g_tokens) cout << "tEQUAL" << endl; RETURN(tEQUAL); }
"<" 		{ if (g_tokens) cout << "tLESS" << endl; RETURN(tLESS); }
">" 		{ if (g_tokens) cout << "tGREATER" << endl; RETURN(tGREATER); }
"=" 		{ if (g_tokens) cout << "tASSIGN" << endl; RETURN(tASSIGN); }
"!" 		{ if (g_tokens) cout << "tBANG" << endl; RETURN(tBANG); }

"!=" 		{ if (g_tokens) cout << "tNOTEQ" << endl; RETURN(tNOTEQ); }
"<=" 		{ if (g_tokens) cout << "tLESSEQ" << endl; RETURN(tLESSEQ); }
">=" 		{ if (g_tokens) cout << "tGREATEREQ" << endl; RETURN(tGREATEREQ); }
":=" 		{ if (g_tokens) cout << "tSHORTDECLARE" << endl; RETURN(tSHORTDECLARE); }
"..." 		{ if (g_tokens) cout << "tELLIPSIS" << endl; RETURN(tELLIPSIS); }

"(" 		{ if (g_tokens) cout << "tLPAREN" << endl; RETURN(tLPAREN); }
"{" 		{ if (g_tokens) cout << "tLBRACE" << endl; RETURN(tLBRACE); }
"[" 		{ if (g_tokens) cout << "tLBRACKET" << endl; RETURN(tLBRACKET); }
"," 		{ if (g_tokens) cout << "tCOMMA" << endl; RETURN(tCOMMA); }
"." 		{ if (g_tokens) cout << "tPERIOD" << endl; RETURN(tPERIOD); }


")" 		{ if (g_tokens) cout << "tRPAREN" << endl; RETURN(tRPAREN); }
"}" 		{ if (g_tokens) cout << "tRBRACE" << endl; RETURN(tRBRACE); }
"]" 		{ if (g_tokens) cout << "tRBRACKET" << endl; RETURN(tRBRACKET); }
";" 		{ if (g_tokens) cout << "tSEMICOLON" << endl; RETURN(tSEMICOLON); }

":" 		{ if (g_tokens) cout << "tCOLON" << endl; RETURN(tCOLON); }
\n		{	
			if (insertSemicolon()) {
				cout << "tSEMICOLON" << endl;
				RETURN(tSEMICOLON);
			}
		}

([a-zA-Z]|"_")([a-zA-Z]|[0-9]|"_")* { 
    yylval.identifier = strdup(yytext);
    if (g_tokens) cout << "tIDENTIFIER(" << yytext << ")" << endl;
    RETURN(tIDENTIFIER);
}

0|([1-9][0-9]*) {
     //yylval.intLiteral = atof(yytext);
    if (g_tokens) cout << "tINTVAL(" << yytext << ")" << endl;
    RETURN(tINTVAL);
}

0[0-7]* {
    //yylval.intLiteral = atof(yytext);
    if (g_tokens) cout << "tINTVAL(" << yytext << ")" << endl;
    RETURN(tINTVAL);
}

0(x|X)[0-9a-fA-F][0-9a-fA-F]* {
    //yylval.intLiteral = atof(yytext);
    if (g_tokens) cout << "tINTVAL(" << yytext << ")" << endl;
    RETURN(tINTVAL);
}

([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*) {
    //yylval.floatLiteral = atof(yytext);
    if (g_tokens) cout << "tFLOATVAL(" << yytext << ")" << endl;
    RETURN(tFLOATVAL);
}

'((\\[abfnrtv\\\'])|[^\\'])\' {  
	//yylval.rune = (yytext);
	if (g_tokens) cout << "tRUNEVAL(" << yytext << ")" << endl;
	RETURN(tRUNEVAL);
}

\"([0-9]|[a-zA-Z]|[\t]|\\{ESCAPE})*\" {
    //yylval.string = (yytext);
    if (g_tokens) cout << "tSTRINGVAL(" << yytext << ")" << endl;
    RETURN(tSTRINGVAL);
}

`(\\.|[^'])*` {
    //yylval.string = (yytext);
    if (g_tokens) cout << "tSTRINGVAL(" << yytext << ")" << endl;
    RETURN(tSTRINGVAL);
}

. { fprintf(stderr, "Error: (line %d) unexpected character '%s'\n", yylineno, yytext); exit(1); }

%%
