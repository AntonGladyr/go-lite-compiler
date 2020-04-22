#ifndef SWITCHSTATEMENT_HPP
#define SWITCHSTATEMENT_HPP

#include <string>
#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Expression/Expression.hpp"
#include "AST/Statement/BlockStatement.hpp"
#include "AST/Statement/CaseClause.hpp"
#include <vector>
#include <utility> 

class CaseClause;

class SwitchStatement : public Statement {
	public:
		Expression *exp = NULL;		
		std::vector<CaseClause*> *clauseList = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();

		SwitchStatement(
			Expression *_exp,
			std::vector<CaseClause*> *_clauseList,
			int _lineno
		) : exp(_exp), clauseList(_clauseList), Statement(_lineno) { }
		
		SwitchStatement() { }
		~SwitchStatement();		
};

#endif
