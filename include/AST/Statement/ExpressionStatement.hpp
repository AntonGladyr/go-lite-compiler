#ifndef EXPRESSIONSTMT_HPP
#define EXPRESSIONSTMT_HPP

#include <string>
#include "Services/Visitor.hpp"
#include <AST/Expression/Expression.hpp>

class ExpressionStatement : public Statement {
	public:	
		Expression *exp = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();
		
		ExpressionStatement(
			Expression *_exp,
			int _lineno
		) : exp(_exp), Statement(_lineno) { }
		
		ExpressionStatement() { }
		~ExpressionStatement();
    };

#endif
