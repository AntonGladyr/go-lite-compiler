#ifndef IFSTMT_CPP
#define IFSTMT_CPP

#include <iostream>
#include "AST/Statement/IfStatement.hpp"

void IfStatement::accept(Visitor& v) {
	//v.visit(this);
}

IfStatement::~IfStatement() {
	std::cout << "IfStatement destroyed" << std::endl;
}

#endif
