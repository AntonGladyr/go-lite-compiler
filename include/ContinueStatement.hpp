//#include "Statement.hpp"
//#include "treeEnums.h"

class ContinueStatement : public Statement {
	public:
		ContinueStatement();
		ContinueStatement() : Statement(k_stmtKindContinue) { }

};
