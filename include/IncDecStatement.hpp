//#include "Statement.hpp"
#include "Expression.hpp"
//#include "treeEnums.h"

class IncDecStatement : public Statement {
	std::string id;
	Expression exp;

	public:
		IncDecStatement();
		IncDecStatement(StatementKind kind, std::string id) : Statement(kind), id{id} { }
		IncDecStatement(StatementKind kind, std::string id, Expression exp) : Statement(kind), id{id}, exp{exp} { }
};
