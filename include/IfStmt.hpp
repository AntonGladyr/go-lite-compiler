#include "Statement.hpp"
#include "Expression.hpp"
#include "Instruction.hpp"
#include "Declaration.hpp"
#include "Instruction.hpp"

class IfStmt: Statement {
	public:
		union val {
			struct { Expression exp; Instruction ins; } ifStmt;
			struct { Declaration decl; Expression exp; Instruction ins; } declIfStmt;
		}
		
		IfStatement(Expression _exp, Instruction _ifIns) : kind{k_stmtKindIfStmt} { }

		IfStatement(Declaration _decl, Expression _exp, Instruction _ifIns) : kind{k_stmtKindDeclIfStmt} { }
}
