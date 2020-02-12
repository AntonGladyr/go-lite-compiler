%{
// #include "parser.tab.hpp" // Token definitions from the parser
#include <string.h>
#include <stdlib.h>

// Stores the line number with each token sent to bison
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
%}

/* Helper definitions */
DIGIT [0-9]

/* Scanner options, line number generation */
%option yylineno

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

"+" {if(g_tokens == 1)cout << ("Plus\n");return tPLUS;}
"-" {if(g_tokens == 1)cout << ("Minus \n");return tMINUS;}
"/" {if(g_tokens == 1)cout << ("Divide \n");return tDIVIDE;}
"*" {if(g_tokens == 1)cout << (" Times \n");return tTIMES;}
"%" {if(g_tokens == 1)cout << ("Modulo \n");return tMODULO;}

"&" {if(g_tokens == 1)cout << (" Single And\n");return tSINGLEAND;}
"|" {if(g_tokens == 1)cout << ("Single Or\n");return tSINGLEOR;}
"^" {if(g_tokens == 1)cout << ("Hat \n");return tHAT;}
"<<" {if(g_tokens == 1)cout << (" Right Shift\n");return tRIGHTSHIFT;}
">>" {if(g_tokens == 1)cout << ("Left Shift\n");return tLEFTSHIFT;}
"&^" {if(g_tokens == 1)cout << ("And hat\n");return tANDHAT;}

"+=" {if(g_tokens == 1)cout << ("Plus equal \n");return tPLUSASSIGN; }
"-=" {if(g_tokens == 1)cout << ("Minus equal\n");return tMINUSASSIGN; }
"*=" {if(g_tokens == 1)cout << ("Times equal\n");return tTIMESASSIGN; }
"/=" {if(g_tokens == 1)cout << ("Divide equal\n");return tDIVIDEASSIGN; }
"%=" {if(g_tokens == 1)cout << ("Modulo equal\n");return tMODULOASSIGN;}

"&=" {if(g_tokens == 1)cout << ("And equal\n");return tANDASSIGN;}
"|=" {if(g_tokens == 1)cout << ("Or equal\n");return tORASSIGN;}
"^=" {if(g_tokens == 1)cout << ("Hat equal\n");return tHATASSIGN;}
"<<=" {if(g_tokens == 1)cout << ("Right shift equal\n");return tRIGHTSHIFTASSIGN;}
"<<=" {if(g_tokens == 1)cout << ("Left shift equal\n");return tLEFTSHIFTASSIGN;}
"&^=" {if(g_tokens == 1)cout << ("And Hat equal\n");return tANDHATASSIGN;}

"&&" {if(g_tokens == 1)cout << ("Logical and\n"); return tAND;}
"||" {if(g_tokens == 1)cout << ("Logical or\n");return tOR;}
"<-" {if(g_tokens == 1)cout << ("Less minus \n");return tLESSMINUS;}
"++" {if(g_tokens == 1)cout << ("Plus Plus \n");return tPLUSPLUS;}
"--" {if(g_tokens == 1)cout << ("Minus Minus \n");return tMINUSMINUS;}

"==" {if(g_tokens == 1)cout << ("Equal\n");  return tEQUAL; }
"<" {if(g_tokens == 1)cout << ("Less than\n");return tLESS;}
">" {if(g_tokens == 1)cout << ("Greater than\n"); return tGREATER;}
"=" { return tASSIGN;}
"!" {if(g_tokens == 1)cout << ("Not \n"); return tNOT;}

"!=" {if(g_tokens == 1)cout << ("Not equal\n"); return tNOT_EQUAL;}
"<=" {if(g_tokens == 1)cout << ("Less or equal than\n"); return tLESS_THAN_OR_EQUAL; }
">=" {if(g_tokens == 1)cout << ("Greater or equal than\n"); return tGREATER_THAN_OR_EQUAL; }
":=" {if(g_tokens == 1)cout << ("Stong Assign\n"); return tSTRONGASSIGN; }
"..." {if(g_tokens == 1)cout << ("DOT DOT DOT\n"); return tDOTDOTDOT; }



"(" {if(g_tokens == 1)cout << ("Left parenthesis\n"); return tLPAREN; }
"{" {if(g_tokens == 1)cout << ("Left brackets\n"); return tLCURL; }
"[" {if(g_tokens == 1)cout << ("Left Square brackets \n"); return tLSQUARE:; }
"," {if(g_tokens == 1)cout << ("Comma \n"); return tCOMMA; }
"." {if(g_tokens == 1)cout << ("Dot\n"); return tDOT; }


")" {if(g_tokens == 1)cout << ("Right parenthesis\n"); return tRPAREN; }
"}" {if(g_tokens == 1)cout << ("right brackets\n"); return tRCURL; }
"]" {if(g_tokens == 1)cout << ("Right parenthesis\n"); return tRSQUARE; }
";" {if(g_tokens == 1)cout << ("Semi-Colon\n"); return tSEMICOLON; }

":" {if(g_tokens == 1)cout << ("Colon \n"); return tCOLON; }


//identifier
([a-zA-Z]|"_")([a-zA-Z]|[0-9]|"_")* { 
    yylval.identifier = (yytext);
    if(g_tokens == 1)
    cout << ("Identifier: "<< yytext << "\n");
    return tIDENTIFIER;
    }

//integer decimal , then octal then hex 
0|([1-9][0-9]*) {
     yylval.intLiteral = atof(yytext);
    if(g_tokens == 1)
    cout << ("Integer constant: "<< yytext << "\n");
    return tINTLITERAL;
}
0[0-7]* {
    yylval.intLiteral = atof(yytext);
    if(g_tokens == 1)
    cout << ("Integer constant: "<< yytext << "\n");
    return tINTLITERAL;
}
0(x|X)[0-9a-fA-F][0-9a-fA-F]* {
    yylval.intLiteral = atof(yytext);
    if(g_tokens == 1)
    cout << ("Integer constant: "<< yytext << "\n");
    return tINTLITERAL;
}
//float
([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*) {
    yylval.floatLiteral = atof(yytext);
    if(g_tokens == 1)
    cout << ("Float constant: "<< yytext << "\n");
    return tFLOATLITERAL;
}

//Character = rune 
'((\\[abfnrtv\\\'])|[^\\'])'{ 
    yylval.rune = (yytext);
    if(g_tokens == 1)
    cout << ("Character: "<< yytext << "\n");
    return tRUNELITERAL;
}
//interpreted String 
\"([0-9]|[a-zA-Z]|[\t]|\\{ESCAPE})*\" {
    yylval.string = (yytext);
    if(g_token == 1)
    cout << ("String variable: "<< yytext << "\n");
    return tSTRINGLITERAL;
}
//raw strings 
'(\\.|[^'])*{
    yylval.string = (yytext);
    if(g_token == 1)
    cout << ("String variable: "<< yytext << "\n");
    return tSTRINGLITERAL;
}
. { fprintf(stderr, "Error: (line %d) unexpected character ‘%s’\n", yylineno, yytext); exit(1); }

%%