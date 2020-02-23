//#include "Statement.hpp"
#include "Expression.hpp"
#include "Declaration.hpp"
#include "Instruction.hpp"

class IfElseStatement : Statement {
	public:
		Expression exp;
		Declaration decl;
		Instruction ifIns;
		Instruction elseIns;
		
		IfElseStatement() { }

		IfElseStatement(StatementKind kind, Expression exp, Instruction ifIns, Instruction elseIns)
			: Statement(kind), exp(exp), ifIns(ifIns), elseIns(elseIns) { }
	
		IfElseStatement(StatementKind kind,
				Declaration decl,
				Expression exp,
				Instruction ifIns,
				Instruction elseIns
		) : Statement(kind), decl(decl), exp(exp), ifIns(ifIns), elseIns(elseIns) { }	
};
