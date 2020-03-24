#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "Program.hpp"
//#include "TypeDeclaration.hpp"
//#include "FunctionDeclaration.hpp"
#include "Expression.hpp"

class Program;
class VariableDeclaration;
class Expression;

class Visitor {
	public:		
		virtual void visit(Program *prg) = 0;
		virtual void visit(VariableDeclaration *varDecl) = 0;
		virtual void visit(Expression *exp) = 0;
		//virtual void visit(TypeDeclaration *typeDecl) = 0;
		//virtual void visit(FunctionDeclaration *funcDecl) = 0;
};

#endif
