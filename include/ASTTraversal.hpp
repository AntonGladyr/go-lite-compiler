#ifndef ASTTRAVERSAL_HPP
#define ASTTRAVERSAL_HPP

#include "Visitor.hpp"
#include "Node.hpp"

class ASTTraversal {
	public:
		ASTTraversal() { }
		static void traverse(Node *node, Visitor& visitor);
		static void clean(Node *node);
};

#endif
