#include "Statement.hpp"
#include "Expression.hpp"
#include <vector>

class AssignStatement : Statement {
    public:
        AssignStatement(vector<string> ids, vector<Expression> rhs) : kind{k_AssignStmtKindTuple} { }

	AssignStatement(string id, string selectorId, Expression opAssign) : kind{k_AssignStmtKindSelector} { }

	AssignStatement(string id, Expression index, Expression rhs) : kind{k_AssignStmtKindIndex} { }
}
