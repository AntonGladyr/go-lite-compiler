#ifndef IFSTATEMENT_HPP
#define IFSTATEMENT_HPP

#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Expression/Expression.hpp"
#include "AST/Declaration/Declaration.hpp"

class IfStatement: public Statement {
	public:
		virtual void accept(Visitor& v) override;
		
		IfStatement() { }
		~IfStatement();
		/*Declaration decl;
		Expression exp;
		Instruction ins;
	
		IfStatement();
	
		IfStatement(Expression exp, Instruction ifIns) : Statement(k_stmtKindIfStmt), exp{exp}, ins{ifIns} { }

		IfStatement(Declaration decl, Expression exp, Instruction ifIns)
			: Statement(k_stmtKindDeclIfStmt), decl{decl}, exp{exp}, ins{ifIns} { }*/
};

#endif
