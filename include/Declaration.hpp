#ifndef DECLARATION_H
#define DECLARATION_H

#include "Node.hpp"

class Declaration : public Node {
    public:
	Declaration() { }	
	virtual void accept(Visitor& v) { };
};

#endif 
