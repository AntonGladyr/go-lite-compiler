#ifndef IDENTIFIEREXP_HPP
#define IDENTIFIEREXP_HPP

#include <string>
#include "Services/Visitor.hpp"
#include <AST/Expression/Expression.hpp>

class IdentifierExp : public Expression {
	public:
		Symbol *symbol = NULL;
		std::string value;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
	
		IdentifierExp(const std::string &_idValue, int _lineno) : value(_idValue), Expression(_lineno) { }
		IdentifierExp() { }
		~IdentifierExp();
};

#endif
