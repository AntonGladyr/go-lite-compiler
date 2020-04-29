#ifndef MAIN_HPP 
#define MAIN_HPP

#include "AST/Program/Program.hpp"
#include "AST/Node.hpp"
#include "Services/Visitor.hpp"
#include "AST/ASTTraversal.hpp"
#include "Services/Weeder.hpp"
#include "Services/PrettyPrinter.hpp"
#include "Services/CodeGenerator.hpp"
#include "SymbolTable/SymbolTable.hpp"

void yyparse();
int yylex();
int g_tokens;

Program *program = NULL;

#endif /* !MAIN_HPP */
