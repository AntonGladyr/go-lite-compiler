#include "IfElseStatement.hpp"

class IfElseStatement : Statement {

	union val {
		struct { Expression exp; Instruction ifIns; Insctruction elseIns; } ifElseStmt;
		struct { Declaration decl; Expression exp; Instruction ifIns; Insctruction elseIns; } declIfElseStmt;
		struct { Expression exp; Instruction ifIns; Instruction elseIns; } ifElseNestedStmt;
		struct { Declaration decl; Expression exp; Instruction ifIns; Instruction elseIns } declIfElseNestedStmt;
	}

	IfStatement(Expression _exp, Instruction _ifIns, Instruction _elseIns) : kind{ k_stmtKindIfElse } {
		val.ifElseStmt.exp = _exp;
		val.ifElseStmt.ifIns = _ifIns;
		val.ifElseStmt.elseIns = _elseIns;
	}
	
	IfStatement(Declaration _decl, Expression _exp, Instruction _ifIns, IfStmt _elseIns)
		: kind{ k_stmtKindDeclIfElse } {
		val.declIfElseStmt.decl = _decl;
		val.declIfElseStmt.exp = _exp;
		val.ifIns = _ifIns;
		val.elseIns = _elseIns;
	}

	IfStatement(Expression _exp, Instruction _ifIns, Instruction _elseIns) : kind{ k_stmtKindIfElseNested } {
		val.ifElseNestedStmt.exp = _exp;
		val.ifElseNestedStmt.ifIns = _ifIns;
		val.ifElseNestedStmt.elseIns = _elseIns;
	}

	IfStatement(Declaration _decl, Expression _exp, Instruction _ifIns, Instruction _elseIns)
		: kind{ k_stmtKindDeclIfElseNested } {
		val.declIfElseNestedStmt.decl = _decl;
		val.declIfElseNestedStmt.exp = _exp;
		val.declIfElseNestedStmt.ifIns = _ifIns;
		val.declIfElseNestedStmt.elseIns = _elseIns; 
	}
}
