#ifndef INTEGERTYPE_EXP_HPP
#define INTEGERTYPE_EXP_HPP

#include <iostream>
#include <string>
#include "AST/Expression/NumericTypeExp.hpp"

class IntegerTypeExp : public NumericTypeExp {
	public:
		virtual void accept(Visitor& v) { };
		virtual std::string toString() { };
		
		IntegerTypeExp(int _lineno) : NumericTypeExp(_lineno) { }
		IntegerTypeExp() { }
		virtual ~IntegerTypeExp() { }
};

#endif

