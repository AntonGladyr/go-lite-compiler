#ifndef STRINGEXP_HPP
#define STRINGEXP_HPP

#include <string>
#include "Visitor.hpp"
#include <Expression.hpp>

class StringExp : public Expression {
	public:
		std::string value;	

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
	
		StringExp(const std::string &_stringValue, int _lineno) : value(_stringValue), Expression(_lineno) { }
		StringExp() { }
		~StringExp();
};

#endif
