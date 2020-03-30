#ifndef IFSTMT_CPP
#define IFSTMT_CPP

#include <sstream>
#include <iostream>
#include "AST/Statement/IfStatement.hpp"

void IfStatement::accept(Visitor& v) {
	v.visit(this);
}

std::string IfStatement::toString() {
	std::stringstream ss;
	ss << "if";
	if (exp)
		ss << " " << exp->toString() << " ";
	return ss.str();
}

IfStatement::~IfStatement() {
	delete exp;
	delete blockStmt;
	std::cout << "IfStatement destroyed" << std::endl;
}

#endif
