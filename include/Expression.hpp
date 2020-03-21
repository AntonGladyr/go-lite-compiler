#ifndef EXPRESSIONS_EXPRESSION_H
#define EXPRESSIONS_EXPRESSION_H

#include <iostream>
#include <string>
#include "Node.hpp"

class Expression : public Node {
	public:
		virtual void accept(Visitor& v) { };
		virtual std::ostream& toString(std::ostream& o) const { };
	
		Expression() { }
		Expression(int _lineno) : Node(_lineno) { }	
};

#endif

