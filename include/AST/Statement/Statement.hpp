#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "AST/Node.hpp"

class Statement : Node {
	public:	
		virtual void accept(Visitor& v) { };
		
		Statement(int _lineno) : Node(_lineno) { }
		Statement() { }	
};


#endif
