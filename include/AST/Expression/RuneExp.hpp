#ifndef RUNEEXP_HPP
#define RUNEEXP_HPP

#include <string>
#include "Services/Visitor.hpp"
#include "AST/Expression/IntegerTypeExp.hpp"

class RuneExp : public IntegerTypeExp {
	public:
		std::string value;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
	
		RuneExp(const std::string &_runeValue, int _lineno);
		RuneExp() { }
		~RuneExp();
};

#endif
