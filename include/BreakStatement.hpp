//#include "Statement.hpp"
//#include "treeEnums.h"

class BreakStatement : public Statement {
	public:
		BreakStatement();
		BreakStatement() : Statement(k_stmtKindBreak) { } 
};
