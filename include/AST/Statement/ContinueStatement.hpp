#ifndef CONTINUESTATEMENT_HPP
#define CONTINUESTATEMENT_HPP

#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"

class ContinueStatement : public Statement {
	public:
		virtual void accept(Visitor& v) override;
		virtual std::string toString();

		ContinueStatement(int _lineno) : Statement(_lineno) { }

		ContinueStatement() { }
		~ContinueStatement();
};

#endif
