#ifndef ASSIGNSTATEMENT_HPP
#define ASSIGNSTATEMENT_HPP

#include "Expression.hpp"
#include <vector>

class AssignStatement : public Statement {
    public:
	/*std::vector<std::string> ids;
	std::vector<Expression> exp_list;
	std::string id;
	std::string selectorId;
	Expression exp;	
	Expression index;
	
	AssignStatement();
		
        AssignStatement(std::vector<std::string> ids, std::vector<Expression> exp_list)
		: Statement(k_stmtKindAssignTuple), ids{ids}, exp_list{exp_list} { };

	AssignStatement(std::string id, std::string selectorId, Expression exp)
		: Statement(k_stmtKindAssignSelector), id{id}, selectorId{selectorId}, exp{exp} { };

	AssignStatement(std::string id, Expression index, Expression exp)
		: Statement(k_stmtKindAssignIndex), id{id}, index{index}, exp{exp} { };*/
};

#endif
