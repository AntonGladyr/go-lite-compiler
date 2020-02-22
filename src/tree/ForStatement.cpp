/*#include "ForStatement.hpp"

class ForStatement : public Statement {
    public:
        ForStatement(Instruction _body) : ForStatement {NULL, _body} { 

        }

        ForStatement(Expression _condition, Instruction _body) 
            : ForStatement{NULL, _condition, NULL, _body} { 

        }
        
        ForStatement(Instruction _initStmt, Expression _condition, Statement _postStmt, Instruction _body)
            : initStmt{_initStmt}, condition{_condition}, postStmt{_postStmt}, body{_body} {
            statementKind = k_stmtKindFor;
        }
}*/
