#ifndef BINARYOPERATOREXP_HPP
#define BINARYOPERATOREXP_HPP

#include <string>
#include "Visitor.hpp"
#include "Expression.hpp"

class BinaryOperatorExp : public Expression {
	public:
		std::string op;
		Expression *lhs;
		Expression *rhs;
		

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
		
		BinaryOperatorExp(const std::string &_op, Expression *_lhs, Expression *_rhs, int _lineno) 
			: op(_op), lhs(_lhs), rhs(_rhs), Expression(_lineno) { }	
		BinaryOperatorExp() { }
		~BinaryOperatorExp();
};

#endif
