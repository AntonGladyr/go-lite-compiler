//#include "Statement.hpp"
//#include "Expression.hpp"
//#include <vector>
//#include "treeEnums.h"

class AssignStatement : public Statement {
    public:
	vector<string> ids;
	vector<Expression> exp_list;
	string id;
	string selectorId;
	Expression exp;	
	Expression index;
		
        AssignStatement(vector<string> ids, vector<Expression> exp_list)
		: kind(k_stmtKindAssignTuple), ids(ids), exp_list(exp_list) { }

	AssignStatement(string id, string selectorId, Expression exp)
		: kind(k_stmtKindAssignSelector), id(id), selectorId(selectorId), exp(exp) { }

	AssignStatement(string id, Expression index, Expression exp)
		: kind(k_stmtKindAssignIndex), id(id), index(index), exp(exp) { }
}
