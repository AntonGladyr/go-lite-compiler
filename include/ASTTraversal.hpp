#ifndef ASTTRAVERSAL_HPP
#define ASTTRAVERSAL_HPP

#include "Visitor.hpp"
#include "Node.hpp"

class ASTTraversal {
	public:
		static void traverse(Node *node, Visitor& visitor);
};

#endif
