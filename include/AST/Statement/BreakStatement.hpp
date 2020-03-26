#ifndef BREAKSTATEMENT_HPP
#define BREAKSTATEMENT_HPP

#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"

class BreakStatement : public Statement {
	public:
		virtual void accept(Visitor& v) override;
		
		BreakStatement() { }
		~BreakStatement();
};

#endif
