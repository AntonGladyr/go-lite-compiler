#ifndef UNARYEXP_HPP
#define UNARYEXP_HPP

#include <string>
#include "Services/Visitor.hpp"
#include <AST/Expression/Expression.hpp>

class UnaryExp : public Expression {
	public:
		std::string op;
		Expression *exp;	
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();
		
		UnaryExp(const std::string &_op, Expression *_exp, int _lineno) 
			: op(_op), exp(_exp), Expression(_lineno) { }
		UnaryExp() { }
		~UnaryExp();
    };

#endif
