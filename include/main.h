#ifndef MAIN_H 
#define MAIN_H

#include "Instruction.hpp"

void yyparse();
int yylex();
int g_tokens;

Instruction *rootIns;

#endif /* !MAIN_H */
