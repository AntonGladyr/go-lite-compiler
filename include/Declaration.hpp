#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include "Node.hpp"

class Declaration : public Node {
	public:
		virtual void accept(Visitor& v) { };
	
		Declaration() { }
		Declaration(int _lineno) : Node(_lineno) { }
};

#endif 
