#ifndef FORSTMT_CPP
#define FORSTMT_CPP

#include <iostream>
#include "AST/Statement/ForStatement.hpp"

void ForStatement::accept(Visitor& v) {
	//v.visit(this);
}

ForStatement::~ForStatement() {
	std::cout << "ForStatement destroyed" << std::endl;
}

#endif
