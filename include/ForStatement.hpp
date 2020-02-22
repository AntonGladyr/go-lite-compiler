//#include "treeEnums.h"
//#include "Statement.hpp"
//#include "Expression.hpp"
//#include "Instruction.hpp"

class ForStatement : public Statement {
	public:
		Instruction initStmt;
        	Expression condition;
        	Statement postStmt;
        	Instruction body;

		ForStatement(Instruction body) : kind(k_stmtKindForInfinite), body(body) { }

		ForStatement(Expression exp, Instruction body) : kind(k_stmtKindForWhile), exp(exp), body(body) { }

		ForStatement(Instruction initStmt, Expression condition, Statement postStmt, Instruction body)
			: kind(k_stmtKindForThreePart),
			  initStmt(initStmt),
			  condition(condition),
			  postStmt(postStmt),
			  body(body)
		{ }
}
