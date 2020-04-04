#ifndef ASSIGNSTATEMENT_HPP
#define ASSIGNSTATEMENT_HPP

#include <vector>
#include "Services/Visitor.hpp"
#include "AST/Expression/Expression.hpp"
#include "AST/Statement/Statement.hpp"

class AssignStatement : public Statement {
	public:	
		std::vector<Expression*> *lhs = NULL;
		std::vector<Expression*> *rhs = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();
	
		AssignStatement(
			std::vector<Expression*> *_lhs,
			std::vector<Expression*> *_rhs,
			int _lineno
		) : lhs(_lhs), rhs(_rhs), Statement(_lineno) { }

		AssignStatement() { }
		~AssignStatement();	
};

#endif
