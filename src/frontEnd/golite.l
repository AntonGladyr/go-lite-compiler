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
<<<<<<< HEAD
/*%option noinput*/
/*%option nounput*/
=======
%option noinput
%option nounput
>>>>>>> 526ae45f9ca2edb4e14c93ce13f9f5a35c696cb5

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

<<<<<<< HEAD
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
"*=" 		{ if (g_tokens) cout << "tMULTASSIGN" << endl; return tMULTASSIGN; }
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

"!=" 		{ if (g_tokens) cout << "tNOTEQ" << endl; return tNOTEQ; }
"<=" 		{ if (g_tokens) cout << "tLESSEQ" << endl; return tLESSEQ; }
">=" 		{ if (g_tokens) cout << "tGREATEREQ" << endl; return tGREATEREQ; }
":=" 		{ if (g_tokens) cout << "tSHORTDEFINE" << endl; return tSHORTDEFINE; }
"..." 		{ if (g_tokens) cout << "tELLIPSIS" << endl; return tELLIPSIS; }

"(" 		{ if (g_tokens) cout << "tLPAREN" << endl; return tLPAREN; }
"{" 		{ if (g_tokens) cout << "tLBRACE" << endl; return tLBRACE; }
"[" 		{ if (g_tokens) cout << "tLBRACKET" << endl; return tLBRACKET; }
"," 		{ if (g_tokens) cout << "tCOMMA" << endl; return tCOMMA; }
"." 		{ if (g_tokens) cout << "tPERIOD" << endl; return tPERIOD; }


")" 		{ if (g_tokens) cout << "tRPAREN" << endl; return insert_semicolon(tRPAREN); }
"}" 		{ if (g_tokens) cout << "tRBRACE" << endl; return insert_semicolon(tRBRACE); }
"]" 		{ if (g_tokens) cout << "tRBRACKET" << endl; return insert_semicolon(tRBRACKET); }
";" 		{ if (g_tokens) cout << "tSEMICOLON" << endl; return tSEMICOLON; }

":" 		{ if (g_tokens) cout << "tCOLON" << endl; return tCOLON; }
\n		{ 	int token = insert_semicolon(tNEWLINE);
			if (token != tNEWLINE) {
=======
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
":=" 		{ if (g_tokens) cout << "tSHORTDEFINE" << endl; RETURN(tSHORTDEFINE); }
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
>>>>>>> 526ae45f9ca2edb4e14c93ce13f9f5a35c696cb5
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

<<<<<<< HEAD
%%

int semicolon = 0;

int insert_semicolon(int token) {
	if (semicolon && token == tNEWLINE) {
		unput('\n');
		semicolon = 0;
		return tSEMICOLON;
	} else {
		int next_symbol = yyinput();
		if (next_symbol == 0) return token;
		
		semicolon = (	(token == tIDENTIFIER && next_symbol == int('\n')) ||
				(token == tINTVAL && next_symbol == int('\n'))||
				(token == tFLOATVAL  && next_symbol == int('\n')) ||
				(token == tRUNEVAL  && next_symbol == int('\n')) ||
				(token == tSTRINGVAL  && next_symbol == int('\n')) ||
				(token == tBREAK  && next_symbol == int('\n')) ||
				(token == tCONTINUE  && next_symbol == int('\n')) ||
				(token == tFALLTHROUGH  && next_symbol == int('\n')) ||
				(token == tRETURN  && next_symbol == int('\n')) ||
				(token == tINC  && next_symbol == int('\n')) ||
				(token == tDEC  && next_symbol == int('\n')) ||
				(token == tRPAREN && next_symbol == int('\n')) ||
				(token == tRBRACKET && next_symbol == int('\n')) ||
				(token == tRBRACE && next_symbol == int('\n'))
		);
		unput(char(next_symbol));
		return token;
	}
}
=======
%%
>>>>>>> 526ae45f9ca2edb4e14c93ce13f9f5a35c696cb5
