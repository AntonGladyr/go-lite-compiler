#ifndef DECLARATION_H
#define DECLARATION_H

#include "Node.hpp"

class Declaration : public Node {
    public:	
	virtual void accept(Visitor& v) { };
	Declaration() { }
	Declaration(int _lineno) : Node(_lineno) { }
};

#endif 
