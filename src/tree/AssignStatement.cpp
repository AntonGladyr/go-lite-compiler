/*#include "AssignStatement.hpp"

class AssignStatement : Statement {
    public:
        AssignStatement(vector<string> ids, vector<Expression> rhs) : kind{k_AssignStmtKindTuple} {
        	val.tupleAssign.ids = ids;
		val.tupleAssign.rhs = rhs;
        }

	AssignStatement(string id, string selectorId, Expression opAssign) : kind{k_AssignStmtKindSelector} {
		val.selectorAssign.id = id;
		val.selectorAssign.opAssign = opAssign;
	}

	AssignStatement(string id, Expression index, Expression rhs) : kind{k_AssignStmtKindIndex} {
		val.indexAssign.id = id;
		val.indexAssign.index = index;
		val.indexAssign.rhs = rhs;
	}
};*/
