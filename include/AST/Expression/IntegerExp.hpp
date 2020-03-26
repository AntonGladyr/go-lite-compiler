#ifndef INTEGEREXP_HPP
#define INTEGEREXP_HPP

#include <string>
#include "Services/Visitor.hpp"
#include "AST/Expression/Expression.hpp"

class IntegerExp : public Expression {
	public:
		int value;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
	
		IntegerExp(int _intValue, int _lineno) : value(_intValue), Expression(_lineno) { }
		IntegerExp() { }
		~IntegerExp();
};

#endif
