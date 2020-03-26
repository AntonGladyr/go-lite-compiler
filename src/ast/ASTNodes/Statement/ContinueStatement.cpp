#ifndef CONTINUESTMT_CPP
#define CONTINUESTMT_CPP

#include <iostream>
#include "AST/Statement/ContinueStatement.hpp"

void ContinueStatement::accept(Visitor& v) {
	//v.visit(this);
}

ContinueStatement::~ContinueStatement() {
	std::cout << "ContinueStatement destroyed" << std::endl;
}

#endif
