#ifndef PRINTSTATEMENT_HPP
#define PRINTSTATEMENT_HPP

#include "Expression.hpp"
#include <vector>

class PrintStatement : public Statement {
	public:
		std::vector<Expression> exp_list;
		
		PrintStatement();
		PrintStatement(StatementKind kind, std::vector<Expression> exp_list) : Statement(kind), exp_list(exp_list) { }
};

#endif
