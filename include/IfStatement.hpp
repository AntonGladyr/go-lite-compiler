//#include "Statement.hpp"
#include "Expression.hpp"
#include "Declaration.h"
#include "Instruction.hpp"

class IfStatement: public Statement {
	public:
		Declaration decl;
		Expression exp;
		Instruction ins;
	
		IfStatement();
	
		IfStatement(Expression exp, Instruction ifIns) : Statement(k_stmtKindIfStmt), exp{exp}, ins{ifIns} { }

		IfStatement(Declaration decl, Expression exp, Instruction ifIns)
			: Statement(k_stmtKindDeclIfStmt), decl{decl}, exp{exp}, ins{ifIns} { }
};
