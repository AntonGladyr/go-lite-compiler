//#include "Statement.hpp"
//#include "Expression.hpp"
//#include "treeEnums.h"

class ReturnStatement : public Statement {
	public:
		Expression exp;

		ReturnStatement() : kind(k_stmtKindReturn);
		ReturnStatement(Expression exp) : kind(k_stmtKindReturnExp), exp(exp);
}
