#ifndef RUNEEXP_HPP
#define RUNEEXP_HPP

#include <string>
#include "Visitor.hpp"
#include <Expression.hpp>

class RuneExp : public Expression {
	public:
		std::string value;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
	
		RuneExp(const std::string &_runeValue, int _lineno);
		RuneExp() { }
		~RuneExp();
};

#endif
