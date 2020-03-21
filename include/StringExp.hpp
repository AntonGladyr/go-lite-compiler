#ifndef STRINGEXP_HPP
#define STRINGEXP_HPP

#include <iostream>
#include <string>
#include "Visitor.hpp"
#include <Expression.hpp>

class StringExp : public Expression {
	public:
		std::string value;

		virtual void accept(Visitor& v) override;
		virtual std::ostream& toString(std::ostream& o) const;
	
		StringExp(const std::string &_stringValue, int _lineno) : value(_stringValue), Expression(_lineno) { }
		StringExp() { }
		~StringExp();
};

#endif
