#ifndef IFELSESTMT_CPP
#define IFELSESTMT_CPP

#include <sstream>
#include <iostream>
#include "AST/Statement/IfElseStatement.hpp"

void IfElseStatement::accept(Visitor& v) {
	v.visit(this);
}

std::string IfElseStatement::toString() {
	//TODO: implement method
	std::stringstream ss;
	ss << "if";
	if (exp)
		ss << " " << exp->toString() << " ";
	return ss.str();
}

IfElseStatement::~IfElseStatement() {
	delete exp;
	delete blockStmt;
	delete elseBlockStmt;
	delete ifStmt;
	
	// for testing purposes
	// std::cout << "IfElseStatement destroyed" << std::endl;
}

#endif
