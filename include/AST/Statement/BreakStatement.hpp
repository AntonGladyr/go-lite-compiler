#ifndef BREAKSTATEMENT_HPP
#define BREAKSTATEMENT_HPP

#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"

class BreakStatement : public Statement {
	public:
		virtual void accept(Visitor& v) override;
		virtual std::string toString();

		BreakStatement(int _lineno) : Statement(_lineno) { }
		
		BreakStatement() { }
		~BreakStatement();
};

#endif
