#include "treeEnums.h"
#include "Statement.hpp"
#include "Expression.hpp"
#include "Instruction.hpp"

class ForStatement : public Statement {
	public:
		Instruction initStmt;
        	Expression condition;
        	Statement postStmt;
        	Instruction body;

        	ForStatement(Instruction _body) : ForStatement {NULL, _body} { }

        	ForStatement(Expression _condition, Instruction _body) 
            		: ForStatement{NULL, _condition, NULL, _body} { 
        	}
        
        	ForStatement(Instruction _initStmt, Expression _condition, Statement _postStmt, Instruction _body)
            		: kind{k_stmtKindFor},
			  initStmt{_initStmt},
			  condition{_condition},
			  postStmt{_postStmt},
			  body{_body}
		{ }
}
