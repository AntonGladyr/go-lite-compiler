#ifndef PRINTSTATEMENT_HPP
#define PRINTSTATEMENT_HPP

#include <vector>
#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Expression/Expression.hpp"

class PrintStatement : public Statement {
	public:
		std::vector<Expression> exp_list;

		virtual void accept(Visitor& v) override;
		
		PrintStatement() { }
		~PrintStatement();
		//PrintStatement(std::vector<Expression> exp_list) : exp_list(exp_list) { }
};

#endif
