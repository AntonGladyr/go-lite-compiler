#include "Statement.hpp"
#include "Expression.hpp"
#include "treeEnums.h"
#include <vector>

class SwitchStatement : public Statement {
	vector<Pair<Expression, Instruction>> case_list;
	Expression exp;
	Declaration decl;
	
	SwitchStatement(vector<Pair<Expression, Instruction>> case_list) : kind(k_stmtSwitch), case_list(case_list);
	SwitchStatement(Expression exp, vector<Pair<Expression, Instruction>> case_list)
		: kind(k_stmtNoExpSwitch), exp(exp), case_lis(case_list);
	SwitchStatement(Declaration decl, Expression exp, vector<Pair<Expression, Instruction>> case_list)
		: kind(k_stmtDeclSwitch), decl(decl), exp(exp), case_list(case_list);	
}
