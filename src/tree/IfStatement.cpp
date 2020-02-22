/*#include "IfStatement.hpp"

class IfStmt: Statement {
	public:
		union val {
			struct { Expression exp; Instruction ins; } ifStmt;
			struct { Declaration decl; Expression exp; Instruction ins; } declIfStmt;
		}
		
		IfStatement(Expression _exp, Instruction _ifIns) : kind{k_stmtKindIfStmt} {
			val.ifStmt.exp = _exp;
			val.ifStmt.declIfStmt = _ifIns;
		}

		IfStatement(Declaration _decl, Expression _exp, Instruction _ifIns) : kind{k_stmtKindDeclIfStmt} {
			val.declIfStmt.decl = _decl;
			val.declIfStmt.exp = _exp;
			val.declIfStmt.ins = _ifIns;
		}		
}*/
