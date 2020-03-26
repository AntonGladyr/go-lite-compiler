#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "AST/Program/Program.hpp"
#include "AST/Declaration/VariableDeclaration.hpp"
#include "AST/Declaration/TypeDeclaration.hpp"
#include "AST/Declaration/FunctionDeclaration.hpp"
#include "AST/Expression/Expression.hpp"

class Program;
class VariableDeclaration;
class TypeDeclaration;
class FunctionDeclaration;

class Visitor {
	public:		
		virtual void visit(Program *prg) = 0;
		virtual void visit(VariableDeclaration *varDecl) = 0;	
		virtual void visit(TypeDeclaration *typeDecl) = 0;
		virtual void visit(FunctionDeclaration *funcDecl) = 0;	
};

#endif
