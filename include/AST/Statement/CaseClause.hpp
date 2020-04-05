#ifndef CASECLAUSE_HPP
#define CASECLAUSE_HPP

#include <vector>
#include "AST/Expression/Expression.hpp"
#include "AST/Statement/BlockStatement.hpp"

enum class SWITCH_CLAUSE { CASE, DEFAULT };

class CaseClause {
	public:
		std::vector<Expression*> *expList = NULL;
		BlockStatement *blockStmt = NULL;
		SWITCH_CLAUSE clauseType;
		int lineno;

		CaseClause(
			std::vector<Expression*> *_expList,
			BlockStatement *_blockStmt,
			SWITCH_CLAUSE _clauseType,
			int _lineno
		) : expList(_expList), blockStmt(_blockStmt), clauseType(_clauseType), lineno(_lineno) { }

		CaseClause() { }
		~CaseClause();
};

#endif
