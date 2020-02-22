//#include "Statement.hpp"
//#include "Expression.hpp"
//#include "treeEnums.h"

class IncDecStatement : public Statement {
	Epxression exp;

	public:
		IncDecStatement(StatementKind kind) : kind(kind);
		IncDecStatement(StatementKind kind, Expression exp) : kind(kind), exp(exp);
}
