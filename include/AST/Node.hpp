#ifndef NODE_HPP
#define NODE_HPP

//#include "Visitor.hpp"

class Visitor;

class Node {
	public:	
		int lineno;

		virtual void accept(Visitor& v) = 0;
	
		Node() { }	
		Node(int _lineno) : lineno(_lineno) { }
};

#endif
