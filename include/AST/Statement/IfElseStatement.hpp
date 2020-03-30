#ifndef IFELSESTATEMENT_HPP
#define IFELSESTATEMENT_HPP

#include <string>
#include "Services/Visitor.hpp"
#include "AST/Statement/BlockStatement.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Expression/Expression.hpp"

class IfStatement;

class IfElseStatement : public Statement {
	public:
		Expression *exp = NULL;
		BlockStatement *blockStmt = NULL;
		BlockStatement *elseBlockStmt = NULL;
		Statement *ifStmt = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();
		
		IfElseStatement(
			Expression *_exp,
			BlockStatement *_blockStmt,
			BlockStatement *_elseBlockStmt,	
			int _lineno
		) : exp(_exp),
		    blockStmt(_blockStmt),
		    elseBlockStmt(_elseBlockStmt), 
		    Statement(_lineno) { }

		IfElseStatement(
			Expression *_exp,
			BlockStatement *_blockStmt,	
			Statement *_ifStmt,
			int _lineno
		) : exp(_exp),
		    blockStmt(_blockStmt), 
		    ifStmt(_ifStmt),
		    Statement(_lineno) { }


		IfElseStatement() { }
		~IfElseStatement();
};

#endif
