#ifndef FORSTATEMENT_HPP
#define FORSTATEMENT_HPP

#include <string>
#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Statement/ExpressionStatement.hpp"
#include "AST/Statement/BlockStatement.hpp"

class ExpressionStatement;

class ForStatement : public Statement {
	public:	
		Statement *initStmt = NULL;
		Statement *postStmt = NULL;
        	Expression *exp = NULL;
		BlockStatement *blockStmt = NULL;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
		
		ForStatement(
			Expression *_exp,
			BlockStatement *_blockStmt,
			int _lineno
		) : exp(_exp), blockStmt(_blockStmt), Statement(_lineno) { }

		ForStatement(
			Statement *_initStmt,
			Expression *_exp,
			Statement *_postStmt,
			BlockStatement *_blockStmt,
			int _lineno
		) : initStmt(_initStmt), exp(_exp), postStmt(_postStmt), blockStmt(_blockStmt), Statement(_lineno) { }
		
		ForStatement() { }
		~ForStatement();		
};

#endif
