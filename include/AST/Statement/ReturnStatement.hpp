#ifndef RETURNSTATEMENT_HPP
#define RETURNSTATEMENT_HPP

//#include "Statement.hpp"
//#include "Expression.hpp"
//#include "treeEnums.h"

#include "AST/Statement/Statement.hpp"
#include "Services/Visitor.hpp"

class ReturnStatement : public Statement {
	public:
		virtual void accept(Visitor& v) override;
		
		ReturnStatement() { }
		~ReturnStatement();
		
		/*Expression exp;

		ReturnStatement() : kind(k_stmtKindReturn) { }
		ReturnStatement(Expression exp) : kind(k_stmtKindReturnExp), exp(exp) { }
		*/
};

#endif
