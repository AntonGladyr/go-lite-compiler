#ifndef EXPRESSIONS_EXPRESSION_H
#define EXPRESSIONS_EXPRESSION_H

#include <iostream>
#include <string>
#include "AST/Node.hpp"

class Expression : public Node {
	public:
		virtual void accept(Visitor& v) { };	
		virtual std::string toString() { };
		
		Expression(int _lineno) : Node(_lineno) { }
		Expression() { }
		virtual ~Expression() { }
};

#endif

