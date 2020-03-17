#ifndef MAIN_H 
#define MAIN_H

#include "Program.hpp"

void yyparse();
int yylex();
int g_tokens;

Program *program;

#endif /* !MAIN_H */
