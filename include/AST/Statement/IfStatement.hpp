#ifndef IFSTATEMENT_HPP
#define IFSTATEMENT_HPP

#include <string>
#include "Services/Visitor.hpp"
#include "AST/Expression/Expression.hpp"
#include "AST/Statement/BlockStatement.hpp"

class IfStatement: public Statement {
	public:
		Expression *exp = NULL;
		BlockStatement *blockStmt = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();

		IfStatement(
			Expression *_exp,
			BlockStatement *_blockStmt,
			int _lineno
		) : exp(_exp), blockStmt(_blockStmt), Statement(_lineno) { }
		
		IfStatement() { }
		~IfStatement();
};

#endif
