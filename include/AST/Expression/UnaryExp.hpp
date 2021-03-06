#ifndef UNARYEXP_HPP
#define UNARYEXP_HPP

#include <string>
#include "Services/Visitor.hpp"
#include <AST/Expression/Expression.hpp>

const std::string UNARY_BANG  = "!";
const std::string UNARY_MINUS = "-";
const std::string UNARY_PLUS  = "+";
const std::string UNARY_BWXOR = "^";

class UnaryExp : public Expression {
	public:
		std::string op;
		Expression *exp = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();
		
		UnaryExp(const std::string &_op, Expression *_exp, int _lineno) 
			: op(_op), exp(_exp), Expression(_lineno) { }
		UnaryExp() { }
		~UnaryExp();
    };

#endif
