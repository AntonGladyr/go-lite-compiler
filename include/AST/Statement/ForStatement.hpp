#ifndef FORSTATEMENT_HPP
#define FORSTATEMENT_HPP

#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Expression/Expression.hpp"

class ForStatement : public Statement {
	public:
		virtual void accept(Visitor& v) override;
		
		ForStatement() { }
		~ForStatement();
		/*Instruction initStmt;
        	Expression condition;
        	Statement postStmt;
        	Instruction body;
		
		ForStatement();

		ForStatement(Instruction body) : Statement(k_stmtKindForInfinite), body{body} { }

		ForStatement(Expression exp, Instruction body) : Statement(k_stmtKindForWhile), condition{exp}, body{body} { }

		ForStatement(Instruction initStmt, Expression condition, Statement postStmt, Instruction body)
			: Statement(k_stmtKindForThreePart),
			  initStmt{initStmt},
			  condition{condition},
			  postStmt{postStmt},
			  body{body}
		{ }*/
};

#endif
