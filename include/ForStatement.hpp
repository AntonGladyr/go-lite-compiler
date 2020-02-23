//#include "treeEnums.h"
//#include "Statement.hpp"
#include "Expression.hpp"
#include "Instruction.hpp"

class ForStatement : public Statement {
	public:
		Instruction initStmt;
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
		{ }
};
