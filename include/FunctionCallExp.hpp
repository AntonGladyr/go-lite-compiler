#ifndef FUNCTIONCALLEXP_HPP
#define FUNCTIONCALLEXP_HPP

#include <vector>
#include <string>
#include "Visitor.hpp"
#include "Expression.hpp"


class FunctionCallExp : public Expression {
	public:	
		Expression *exp;
		std::vector<Expression*> expList;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
			
		FunctionCallExp(Expression *_exp, std::vector<Expression*> _expList, int _lineno) :
			exp(_exp), expList(_expList), Expression(_lineno) { }
		FunctionCallExp() { }
		~FunctionCallExp();	
};

#endif
