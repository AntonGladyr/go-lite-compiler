//#include "Statement.hpp"
//#include "Expression.hpp"
//#include "treeEnums.h"

class IncDecStatement : public Statement {
	string id;
	Epxression exp;

	public:
		IncDecStatement(StatementKind kind, string id) : kind(kind), id(id);
		IncDecStatement(StatementKind kind, string id, Expression exp) : kind(kind), id(id), exp(exp);
}
