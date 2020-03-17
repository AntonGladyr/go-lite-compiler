#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "Program.hpp"
//#include "TypeDeclaration.hpp"
//#include "FunctionDeclaration.hpp"

class Program;

class Visitor {
	public:		
		virtual void visit(Program *prg) = 0;
		//virtual void visit(TypeDeclaration *typeDecl) = 0;
		//virtual void visit(FunctionDeclaration *funcDecl) = 0;	
};

#endif
