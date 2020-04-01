#ifndef DECLARATION_HPP
#define DECLARATION_HPP

#include "AST/Node.hpp"
#include "SymbolTable/Symbol.hpp"

class Declaration : public Node {
	public:
		Symbol *symbol = NULL;
		
		virtual void accept(Visitor& v) { };
		virtual std::string symbolToStr() { };
		virtual std::string symbolTypeToStr() { };
		virtual std::string toString() { };
		
		Declaration(int _lineno) : Node(_lineno) { }
		Declaration() { }
		virtual ~Declaration() { }
};

#endif 
