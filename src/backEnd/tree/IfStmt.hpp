#include "Statement.hpp"
#include "Expression.hpp"
#include "Instruction.hpp"
#include "Declaration.hpp"
#include "Instruction.hpp"

class IfStmt: Statement {
	private:
		Expression exp;
		Instruction ifInstr;
		Declaration decl;
		Instruction elseInstr;
	public:
		
		IfStatement(Expression _exp, Instruction _ifIns) : IfStatement(NULL, _exp, _ifIns, NULL) {
		}

		IfStatement(Declaration _decl, Expression _exp, Instruction _ifIns)
			: IfStatement(_decl, _exp, _ifIns, NULL) {
			
		}	

		IfStatement(Expression _exp, Instruction _ifIns, Instruction _elseIns)
			: IfStatement(NULL, _exp, _ifIns, _elseIns) {
			
		}
	
		IfStatement(Declaration _decl, Expression _exp, Instruction _ins, IfStmt _elseStmt)
			: decl(_decl), exp(_exp), ifInstr(_ifIns), elseInstr(_elseIns) {
			
		}

		IfStatement(Expression _exp, Instruction _ifIns, Instruction _elseIns)
			: IfStatement(NULL, _exp, _ifIns, _elseIns) {
		
		}

		IfStatement(Declaration _decl, Expression _exp, Instruction _ifIns, Instruction _elseIns)
			: decl(_decl), exp(_exp), ifInstr(_ifIns), elseInstr(_elseIns) {
			statementKind = k_statemnetKindIf;
		}
		
}	
