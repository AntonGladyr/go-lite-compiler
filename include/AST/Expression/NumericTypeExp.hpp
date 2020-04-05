#ifndef NUMERICTYPE_EXP_HPP
#define NUMERICTYPE_EXP_HPP

#include <iostream>
#include <string>
#include "AST/Expression/Expression.hpp"

class NumericTypeExp : public Expression {
	public:
		virtual void accept(Visitor& v) { };
		virtual std::string toString() { };
		
		NumericTypeExp(int _lineno) : Expression(_lineno) { }
		NumericTypeExp() { }
		virtual ~NumericTypeExp() { }
};

#endif
