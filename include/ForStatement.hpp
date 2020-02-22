#include "Statement.hpp"
#include "Instruction.hpp"
#include "Expression.hpp"

class ForStatement : public Statement {
    private:
        Instruction initStmt;
        Expression condition;
        Statement postStmt;
        Instruction body;
    public:
        ForStatement(Instruction _body) : ForStatement {NULL, _body} { }

        ForStatement(Expression _condition, Instruction _body) 
            : ForStatement{NULL, _condition, NULL, _body} { 
        }
        
        ForStatement(Instruction _initStmt, Expression _condition, Statement _postStmt, Instruction _body)
            : initStmt{_initStmt}, condition{_condition}, postStmt{_postStmt}, body{_body} {
        }
}
