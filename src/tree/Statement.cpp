/*#include "Statement.hpp"

class Statement : Instruction {
	protected:
		StatementKind kind;
	public:
		union val {
			struct { Expression exp; } incDecStmt;
			struct { Experssion expList; bool isPrintLn; } printStmt;
			struct { Expression exp; } returnStmt;
			struct { vector<string> ids; vector<Expression> rhs; } tupleAssign;
			struct { string id; string selectorId; Expression opAssign; } selectorAssign;
			struct { string id; Expression index; Expression rhs; } indexAssign;
			struct { vector<Pair<Expression, Instruction>>; } noExpSwitchStmt;
			struct { Expression exp; vector<Pair<Expression, Instruction>>; } switchStmt;
			struct { Declaration decl; Expression exp; vector<Pair<Expression, Instruction>>; } declSwitchStmt;
		}			
	
		Statement(StatementKind kind, Expression exp) {
			this.kind = kind;
			val.exp = exp;
		}

		Statement(Expression expList, bool isPrintLn) : kind{k_stmtKindPrint} {
			val.printStmt.expList = expList;
			val.printStmt.isPrintLn = isPrintLn;
		}

		Statement(ReturnStmt returnStmt, Expression exp) : kind{k_stmtKindReturn} {
			val.returnStmt.exp = exp;
		}
	
		Statement(StatementKind k_stmtKindBreak) {
			this.kind = k_stmtKindBreak;
		}

		Statement(StatementKind k_stmtKindContinue) {
			this.kind = k_stmtKindContinue;
		}			
}*/
