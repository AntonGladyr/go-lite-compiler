#ifndef DECLARATION_H
#define DECLARATION_H

#include <vector>
#include <string>

#include "tree.h"
#include "Node.hpp"

class Declaration : Node {
    public:
        DeclarationKind kind;
	
	Declaration() { }
	Declaration(DeclarationKind kind) : kind{kind} { }
};

#endif 
