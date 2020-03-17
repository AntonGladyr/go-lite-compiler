#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "Node.hpp"

class Visitor {
	public:
		Visitor();
		void visit(Node node);
}

#endif
