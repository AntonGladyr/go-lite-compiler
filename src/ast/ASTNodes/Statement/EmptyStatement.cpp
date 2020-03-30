#ifndef EMPTYSTMT_CPP
#define EMPTYSTMT_CPP

#include <sstream>
#include <iostream>
#include "AST/Statement/EmptyStatement.hpp"

void EmptyStatement::accept(Visitor& v) {
	v.visit(this);
}

EmptyStatement::~EmptyStatement() {
	// for testing purposes
	// std::cout << "EmptyStatement destroyed" << std::endl;
}

#endif
