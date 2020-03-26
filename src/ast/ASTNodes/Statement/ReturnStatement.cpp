#ifndef RETURNSTMT_CPP
#define RETURNSTMT_CPP

#include <iostream>
#include "AST/Statement/ReturnStatement.hpp"

void ReturnStatement::accept(Visitor& v) {
	//v.visit(this);
}

ReturnStatement::~ReturnStatement() {
	std::cout << "ReturnStatement destroyed" << std::endl;
}

#endif
