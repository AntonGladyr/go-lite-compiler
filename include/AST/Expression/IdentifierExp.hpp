#ifndef IDENTIFIEREXP_HPP
#define IDENTIFIEREXP_HPP

#include <string>
#include "Services/Visitor.hpp"
#include <AST/Expression/Expression.hpp>

class IdentifierExp : public Expression {
	public:
		std::string value;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
	
		IdentifierExp(std::string _idValue, int _lineno) : value(_idValue), Expression(_lineno) { }
		IdentifierExp() { }
		~IdentifierExp();
};

#endif