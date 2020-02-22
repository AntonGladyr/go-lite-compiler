#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "Node.hpp"
#include "StatementEnum.hpp"

class Statement : Node {
	public:
		StatementKind kind;	
};


#endif