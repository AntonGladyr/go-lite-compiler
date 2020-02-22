#include "Statement.hpp"
#include "Expression.hpp"
#include "Instruction.hpp"
#include "Declaration.hpp"
#include "Instruction.hpp"

class IfElseStatement : Statement {
	public:
		Expression exp;
		Declaration decl;
		Instruction ifIns;
		Instruction elseIns;
		
		IfStatement(Expression exp, Instruction ifIns, Instruction elseIns)
			: kind(k_stmtKindIfElse), exp(exp), ifIns(ifIns), elseIns(elseIns) { }
	
		IfStatement(Declaration decl, Expression exp, Instruction ifIns, IfStmt elseIns)
			: kind(k_stmtKindDeclIfElse), decl(decl), exp(exp), ifIns(ifIns), elseIns(elseIns) { }

		IfStatement(Expression exp, Instruction ifIns, Instruction elseIns)
			: kind(k_stmtKindIfElseNested), exp(exp), ifIns(ifIns), elseIns(elseIns) { }

		IfStatement(Declaration decl, Expression exp, Instruction ifIns, Instruction elseIns)
			: kind(k_stmtKindDeclIfElseNested), decl(decl), exp(exp), ifIns(ifIns), elseIns(elseIns) { }
}
