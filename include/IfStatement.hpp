#include "Statement.hpp"
#include "Expression.hpp"
#include "Declaration.hpp"
#include "Instruction.hpp"

class IfStatement: public Statement {
	public:
		Declaration decl;
		Expression exp;
		Instruction ins;
		
		IfStatement(Expression exp, Instruction ifIns) : kind(k_stmtKindIfStmt), exp(exp), ins(IfIns) { }

		IfStatement(Declaration decl, Expression exp, Instruction ifIns)
			: kind(k_stmtKindDeclIfStmt), decl(decl), exp(exp), ins(ifIns) { }
}
