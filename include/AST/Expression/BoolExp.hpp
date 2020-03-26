#ifndef BOOLEXP_HPP
#define BOOLEXP_HPP

#include <string>
#include "Services/Visitor.hpp"
#include "AST/Expression/Expression.hpp"

class BoolExp : public Expression {
	public:
		bool value;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
	
		BoolExp(bool _boolValue, int _lineno) : value(_boolValue), Expression(_lineno) { }
		BoolExp() { }
		~BoolExp();
};

#endif
