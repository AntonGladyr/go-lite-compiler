#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include "AST/Node.hpp"

class Declaration : public Node {
	public:
		virtual void accept(Visitor& v) { };
		virtual std::string toString() { };
		
		Declaration(int _lineno) : Node(_lineno) { }
		Declaration() { }
		virtual ~Declaration() { }
};

#endif 
