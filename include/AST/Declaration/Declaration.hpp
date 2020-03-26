#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include "AST/Node.hpp"

class Declaration : public Node {
	public:
		virtual void accept(Visitor& v) { };
		virtual std::string toString() { };
	
		Declaration() { }
		Declaration(int _lineno) : Node(_lineno) { }
};

#endif 
