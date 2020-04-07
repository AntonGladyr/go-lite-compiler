#ifndef EXPRESSIONS_EXPRESSION_HPP
#define EXPRESSIONS_EXPRESSION_HPP

#include <iostream>
#include <string>
#include "AST/Node.hpp"

class Expression : public Node {
	public:
		Symbol *symbol = NULL;

		std::string type;
		virtual void accept(Visitor& v) { };
		virtual std::string toString() { };
		
		Expression(int _lineno) : Node(_lineno) { }
		Expression() { }
		virtual ~Expression() { }
};

#endif
