%{
#include "y.tab.h"

using namespace std;
// Stores the line number with each token sent to bison
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;

int g_tokens = 0;

%}

/* Helper definitions */
DIGIT [0-9]

/* Scanner options, line number generation */
%option yylineno

%%
\/\/(.*)
\/\*(\*(?!\/)|[^*])*\*\/

"break"		{ if (g_tokens) cout << "tBREAK" << endl; return tBREAK; }
"case"		{ if (g_tokens) cout << "tCASE" << endl; return tCASE; }
"chan"		{ if (g_tokens) cout << "tCHAN" << endl; return tCHAN; }
"const" 	{ if (g_tokens) cout << "tCONST" << endl; return tCONST; }
"continue"	{ if (g_tokens) cout << "tCONTINUE" << endl; return tCONTINUE; }
"default"	{ if (g_tokens) cout << "tDEFAULT" << endl; return tDEFAULT; }
"defer"		{ if (g_tokens) cout << "tDEFER" << endl; return tDEFER; }
"else"		{ if (g_tokens) cout << "tELSE" << endl; return tELSE; }
"fallthrough"	{ if (g_tokens) cout << "tFALLTHROUGH" << endl; return tFALLTHROUGH; }
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
"return"	{ if (g_tokens) cout << "tRETURN" << endl; return tRETURN; }
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

.		{ stderr << "Error: (line" << yylineno << ") unexpected character" << yytext << endl; exit(1); }
%%
