#ifndef EXPRESSIONS_EXPRESSION_HPP
#define EXPRESSIONS_EXPRESSION_HPP

#include <iostream>
#include <string>
#include "AST/Node.hpp"
#include "TypeDescriptorTable/TypeDescriptor.hpp"
#include "SymbolTable/Symbol.hpp"

class Expression : public Node {
	public:
		TypeDescriptor type;
		Symbol *symbol = NULL;	
		
		virtual void accept(Visitor& v) { };
		virtual std::string toString() { };
		
		Expression(int _lineno) : Node(_lineno) { }
		Expression() { }
		virtual ~Expression() { }
};

#endif
