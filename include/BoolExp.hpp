#ifndef BOOLEXP_HPP
#define BOOLEXP_HPP

#include <iostream>
#include "Visitor.hpp"
#include <Expression.hpp>

class BoolExp : public Expression {
	public:
		bool value;

		virtual void accept(Visitor& v) override;
		virtual std::ostream& toString(std::ostream& o) const;
	
		BoolExp(bool _boolValue, int _lineno) : value(_boolValue), Expression(_lineno) { }
		BoolExp() { }
		~BoolExp();
};

#endif
