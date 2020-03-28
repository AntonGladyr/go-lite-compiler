#ifndef ASTTRAVERSAL_HPP
#define ASTTRAVERSAL_HPP

#include "Services/Visitor.hpp"
#include "AST/Node.hpp"

class ASTTraversal {
	public:
		ASTTraversal() { }
		static void traverse(Node *node, Visitor& visitor);	
};

#endif
