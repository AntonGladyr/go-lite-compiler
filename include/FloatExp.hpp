#ifndef FLOATEXP_HPP
#define FLOATEXP_HPP

#include <iostream>
#include "Visitor.hpp"
#include <Expression.hpp>

class FloatExp : public Expression {
	public:
		double value;

		virtual void accept(Visitor& v) override;
		virtual std::ostream& toString(std::ostream& o) const;
	
		FloatExp(double _floatValue, int _lineno) : value(_floatValue), Expression(_lineno) { }
		FloatExp() { }
		~FloatExp();
};

#endif
