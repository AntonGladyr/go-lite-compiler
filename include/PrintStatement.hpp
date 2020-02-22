//#include "Statement.hpp"
//#include "treeEnums.h"
//#include "Expression.hpp"
//#include <vector>

class PrintStatement : public Statement {
	public:
		vector<Expression> exp_list;
		
		PrintStatement(StatementKind kind, vector<Expression> exp_list) : kind(kind), exp_list(exp_list);
}
