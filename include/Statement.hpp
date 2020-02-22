#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "Node.hpp"
#include "treeEnums.h"

class Statement : Node {
	public:
		StatementKind kind;	
};


#endif