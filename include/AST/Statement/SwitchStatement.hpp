#ifndef SWITCHSTATEMENT_HPP
#define SWITCHSTATEMENT_HPP

#include <string>
#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Expression/Expression.hpp"
#include "AST/Statement/BlockStatement.hpp"
#include <vector>
#include <utility> 

enum class SWITCH_CLAUSE { CASE, DEFAULT };
typedef std::pair<std::vector<Expression*>*, BlockStatement*> case_clause;
typedef std::vector<std::pair<case_clause*, SWITCH_CLAUSE>*> clause_list;

class SwitchStatement : public Statement {
	public:
		Expression *exp = NULL;		
		clause_list *clauseList = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();

		SwitchStatement(
			Expression *_exp,
			clause_list *_clauseList,
			int _lineno
		) : exp(_exp), clauseList(_clauseList), Statement(_lineno) { }
		
		SwitchStatement() { }
		~SwitchStatement();		
};

#endif
