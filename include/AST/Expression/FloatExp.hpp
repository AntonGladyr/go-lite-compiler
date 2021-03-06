#ifndef FLOATEXP_HPP
#define FLOATEXP_HPP

#include <string>
#include "Services/Visitor.hpp"
#include "AST/Expression/Expression.hpp"

class FloatExp : public Expression {
	public:
		double value;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
	
		FloatExp(double _floatValue, int _lineno) : value(_floatValue), Expression(_lineno) { }
		FloatExp() { }
		~FloatExp();
};

#endif
