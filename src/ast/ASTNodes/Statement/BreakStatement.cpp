#ifndef BREAKSTMT_CPP
#define BREAKSTMT_CPP

#include <iostream>
#include "AST/Statement/BreakStatement.hpp"

void BreakStatement::accept(Visitor& v) {
	//v.visit(this);
}

BreakStatement::~BreakStatement() {
	std::cout << "BreakStatement destroyed" << std::endl;
}

#endif
