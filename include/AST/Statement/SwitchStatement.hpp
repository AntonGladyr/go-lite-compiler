#ifndef SWITCHSTATEMENT_HPP
#define SWITCHSTATEMENT_HPP

#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Expression/Expression.hpp"
#include <vector>
#include <utility> 

class SwitchStatement : public Statement {
	public:
		virtual void accept(Visitor& v) override;
		
		SwitchStatement() { }
		~SwitchStatement();
		
	/*std::vector<std::pair<Expression, Instruction>> case_list;
	Expression exp;
	Declaration decl;

	SwitchStatement();
	SwitchStatement(std::vector<std::pair<Expression, Instruction>> case_list) : Statement(k_stmtSwitch), case_list(case_list) { }
	SwitchStatement(Expression exp, std::vector<std::pair<Expression, Instruction>> case_list)
		: Statement(k_stmtNoExpSwitch), exp(exp), case_list(case_list) { }
	SwitchStatement(Declaration decl, std::vector<std::pair<Expression, Instruction>> case_list)
		: Statement(k_stmtDeclSwitch), decl(decl), exp(exp), case_list(case_list) { }*/
};

#endif
