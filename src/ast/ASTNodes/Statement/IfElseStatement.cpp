#ifndef IFELSESTMT_CPP
#define IFELSESTMT_CPP

#include <iostream>
#include "AST/Statement/IfElseStatement.hpp"

void IfElseStatement::accept(Visitor& v) {
	//v.visit(this);
}

IfElseStatement::~IfElseStatement() {
	std::cout << "IfElseStatement destroyed" << std::endl;
}

#endif
