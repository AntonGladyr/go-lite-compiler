#ifndef BLOCKSTMT_HPP
#define BLOCKSTMT_HPP

#include <string>
#include <vector>
#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"

class BlockStatement : public Statement {
	public:
		std::vector<Statement*> *stmtList;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();

		BlockStatement(
			std::vector<Statement*> *_stmtList,
			int _lineno
		) : stmtList(_stmtList), Statement(_lineno) { }
	
		BlockStatement() { }
		~BlockStatement();
};

#endif
