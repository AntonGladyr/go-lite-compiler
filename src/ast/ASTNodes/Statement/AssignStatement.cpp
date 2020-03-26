#ifndef ASSIGNSTMT_CPP
#define ASSIGNSTMT_CPP

#include <iostream>
#include "AST/Statement/AssignStatement.hpp"

void AssignStatement::accept(Visitor& v) {
	//v.visit(this);
}

AssignStatement::~AssignStatement() {
	std::cout << "AssignStatement destroyed" << std::endl;
}

#endif
