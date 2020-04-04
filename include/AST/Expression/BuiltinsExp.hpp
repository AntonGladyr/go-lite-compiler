#ifndef BUILTINS_H
#define BUILTINS_H

#include <string>
#include "Services/Visitor.hpp"
#include <AST/Expression/Expression.hpp>

const std::string BUILTIN_LEN =  "len";
const std::string BUILTIN_CAP =  "cap";

class BuiltinsExp : public Expression {
	public:
		std::string name;
		Expression *exp = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();
		
		BuiltinsExp(const std::string &_name, Expression *_exp, int _lineno) 
			: name(_name), exp(_exp), Expression(_lineno) { }
		BuiltinsExp() { }
		~BuiltinsExp();
};

#endif
