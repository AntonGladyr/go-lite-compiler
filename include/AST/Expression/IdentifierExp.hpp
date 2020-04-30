#ifndef IDENTIFIEREXP_HPP
#define IDENTIFIEREXP_HPP

#include <string>
#include "Services/Visitor.hpp"
#include <AST/Expression/Expression.hpp>
#include "AST/Node.hpp"

class IdentifierExp : public Expression {
	public:
		std::string name;
		Symbol *symbol = NULL;
		Node *parentNode = NULL;
		Symbol *typeSymbol = NULL; // pointer to the type in symbol table

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
	
		IdentifierExp(
			const std::string &_name,
			int _lineno
		) : name(_name), Expression(_lineno) { }
		
		IdentifierExp() { }
		~IdentifierExp();
};

#endif
