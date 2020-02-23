//#include "Statement.hpp"
#include "Expression.hpp"
//#include "treeEnums.h"
#include <vector>

class SwitchStatement : public Statement {
	std::vector<Pair<Expression, Instruction>> case_list;
	Expression exp;
	Declaration decl;

	SwitchStatement();
	SwitchStatement(std::vector<Pair<Expression, Instruction>> case_list) : Statement(k_stmtSwitch), case_list(case_list) { }
	SwitchStatement(Expression exp, std::vector<Pair<Expression, Instruction>> case_list)
		: Statement(k_stmtNoExpSwitch), exp(exp), case_lis(case_list) { }
	SwitchStatement(Declaration decl, std::vector<Pair<Expression, Instruction>> case_list)
		: Statement(k_stmtDeclSwitch), decl(decl), exp(exp), case_list(case_list) { }
};
