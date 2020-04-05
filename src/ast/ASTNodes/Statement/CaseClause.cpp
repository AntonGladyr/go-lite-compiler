#ifndef CASECLAUSE_CPP
#define CASECLAUSE_CPP

#include "AST/Statement/CaseClause.hpp"

CaseClause::~CaseClause() {
	if (expList) {
		for(auto const& exp : *expList) {
			delete exp;
		}
		delete expList;
	}
	if (blockStmt) delete blockStmt;	
}

#endif
