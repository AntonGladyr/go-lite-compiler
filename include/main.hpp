#ifndef MAIN_HPP 
#define MAIN_HPP

#include "Program.hpp"
#include "Node.hpp"
#include "Visitor.hpp"
#include "PrettyPrinterVisitor.hpp"

void yyparse();
int yylex();
int g_tokens;

Program *program;

#endif /* !MAIN_HPP */
