#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "tree.h"
#include "Node.hpp"

class Statement : Node {
	public:
		StatementKind kind;
	
	Statement();
	Statement(StatementKind kind) : kind{kind} { }
};


#endif
