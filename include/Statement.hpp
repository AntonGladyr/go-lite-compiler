#include "Instruction.hpp"
#include "ForStatement.hpp"
#include "AssignStatement.hpp"
#include "IfStmt.hpp"
#include "SwitchStmt.hpp"
#include "Expression.hpp"

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
	
		Statement(StatementKind kind, Expression exp) { }

		Statement(Expression expList, bool isPrintLn) : kind{k_stmtKindPrint} { }

		Statement(ReturnStmt returnStmt, Expression exp) : kind{k_stmtKindReturn} { }
	
		Statement(StatementKind k_stmtKindBreak) { }

		Statement(StatementKind k_stmtKindContinue) { }			
}
