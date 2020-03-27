#ifndef EMPTYSTMT_CPP
#define EMPTYSTMT_CPP

#include <sstream>
#include <iostream>
#include "AST/Statement/EmptyStatement.hpp"

void EmptyStatement::accept(Visitor& v) {
	v.visit(this);
}

EmptyStatement::~EmptyStatement() {
	std::cout << "EmptyStatement destroyed" << std::endl;
}

#endif
