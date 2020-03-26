#ifndef IFELSESTATEMENT_HPP
#define IFELSESTATEMENT_HPP

#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Expression/Expression.hpp"
#include "AST/Declaration/Declaration.hpp"

class IfElseStatement : Statement {
	public:
		virtual void accept(Visitor& v) override;
		
		IfElseStatement() { }
		~IfElseStatement();
		
		/*Expression exp;
		Declaration decl;
		Instruction ifIns;
		Instruction elseIns;
		
		IfElseStatement() { }

		IfElseStatement(StatementKind kind, Expression exp, Instruction ifIns, Instruction elseIns)
			: Statement(kind), exp(exp), ifIns(ifIns), elseIns(elseIns) { }
	
		IfElseStatement(StatementKind kind,
				Declaration decl,
				Expression exp,
				Instruction ifIns,
				Instruction elseIns
		) : Statement(kind), decl(decl), exp(exp), ifIns(ifIns), elseIns(elseIns) { }	*/
};

#endif
