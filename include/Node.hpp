#ifndef NODE_HPP
#define NODE_HPP

#include "Visitor.hpp"

class Visitor;

class Node {
	public:	
		virtual void accept(Visitor& v) = 0;
		int lineno;
};

#endif
