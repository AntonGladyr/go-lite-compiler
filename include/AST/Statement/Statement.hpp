#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "AST/Node.hpp"
#include "AST/Declaration/FunctionDeclaration.hpp"

class FunctionDeclaration;

class Statement : public Node {
	public:	
		virtual void accept(Visitor& v) { };
		virtual std::string toString() { };

		FunctionDeclaration *functionNode = NULL;
		
		Statement(int _lineno) : Node(_lineno) { }
		Statement() { }
		virtual ~Statement() { }
};

#endif
