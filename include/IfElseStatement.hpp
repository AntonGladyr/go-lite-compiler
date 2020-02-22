#include "Statement.hpp"
#include "Expression.hpp"
#include "Instruction.hpp"
#include "Declaration.hpp"
#include "Instruction.hpp"

class IfElseStatement : Statement {

	union val {
		struct { Expression exp; Instruction ifIns; Insctruction elseIns; } ifElseStmt;
		struct { Declaration decl; Expression exp; Instruction ifIns; Insctruction elseIns; } declIfElseStmt;
		struct { Expression exp; Instruction ifIns; Instruction elseIns; } ifElseNestedStmt;
		struct { Declaration decl; Expression exp; Instruction ifIns; Instruction elseIns } declIfElseNestedStmt;
	}

	IfStatement(Expression _exp, Instruction _ifIns, Instruction _elseIns) : kind{ k_stmtKindIfElse } {
	}
	
	IfStatement(Declaration _decl, Expression _exp, Instruction _ifIns, IfStmt _elseIns)
		: kind{ k_stmtKindDeclIfElse } {
	}

	IfStatement(Expression _exp, Instruction _ifIns, Instruction _elseIns) : kind{ k_stmtKindIfElseNested } {
	}

	IfStatement(Declaration _decl, Expression _exp, Instruction _ifIns, Instruction _elseIns)
		: kind{ k_stmtKindDeclIfElseNested } {
	}
}
