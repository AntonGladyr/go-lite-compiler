#ifndef INTEGEREXP_HPP
#define INTEGEREXP_HPP

#include <iostream>
#include "Visitor.hpp"
#include <Expression.hpp>

class IntegerExp : public Expression {
	public:
		int value;

		virtual void accept(Visitor& v) override;
		virtual std::ostream& toString(std::ostream& o) const;
	
		IntegerExp(int _intValue, int _lineno) : value(_intValue), Expression(_lineno) { }
		IntegerExp() { }
		~IntegerExp();
};

#endif
