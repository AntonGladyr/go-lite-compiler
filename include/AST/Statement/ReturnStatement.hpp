#ifndef RETURNSTMT_HPP
#define RETURNSTMT_HPP

#include <string>
#include <vector>
#include "Services/Visitor.hpp"
#include "AST/Expression/Expression.hpp"

class ReturnStatement : public Statement {
	public:
		Expression *exp = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();

		ReturnStatement(
			Expression *_exp,
			int _lineno
		) : exp(_exp), Statement(_lineno) { }

		ReturnStatement(
			int _lineno
		) : Statement(_lineno) { }
	
		ReturnStatement() { }
		~ReturnStatement();
};

#endif
