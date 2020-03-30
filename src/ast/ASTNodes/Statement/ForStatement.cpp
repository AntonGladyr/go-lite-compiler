#ifndef FORSTMT_CPP
#define FORSTMT_CPP

#include <iostream>
#include <sstream>
#include "AST/Statement/ForStatement.hpp"

void ForStatement::accept(Visitor& v) {
	v.visit(this);
}

std::string ForStatement::toString() {
	//TODO: fix block output
	std::stringstream ss;	
	ss << "for";
	if (initStmt && postStmt)
		ss << " " << initStmt->toString() << ";";
	if (exp)
		ss << " " << exp->toString();
	if (initStmt && postStmt)
		ss << "; " << postStmt->toString();
	return ss.str();
}


ForStatement::~ForStatement() {
	if (initStmt) delete initStmt;
	if (exp) delete exp;
	if (postStmt) delete postStmt;
	delete blockStmt;
	std::cout << "ForStatement destroyed" << std::endl;
}

#endif
