#ifndef FLOATEXP_HPP
#define FLOATEXP_HPP

#include <string>
#include "Services/Visitor.hpp"
#include "AST/Expression/NumericTypeExp.hpp"

class FloatExp : public NumericTypeExp {
	public:
		double value;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
	
		FloatExp(double _floatValue, int _lineno) : value(_floatValue), NumericTypeExp(_lineno) { }
		FloatExp() { }
		~FloatExp();
};

#endif
