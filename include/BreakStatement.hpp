#include "Statement.hpp"
#include "treeEnums.h"

class BreakStatement : public Statement {
	public:
		BreakStatement() : kind(k_stmtKindBreak); 
}
