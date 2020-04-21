#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "AST/Node.hpp"

class Statement : public Node {
	public:	
		virtual void accept(Visitor& v) { };
		virtual std::string toString() { };

		Statement *parentBlockNode = NULL;
		
		Statement(int _lineno) : Node(_lineno) { }
		Statement() { }
		virtual ~Statement() { }
};

#endif
