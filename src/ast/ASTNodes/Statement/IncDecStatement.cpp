#ifndef INCDECSTMT_CPP
#define INCDECSTMT_CPP

#include <iostream>
#include "AST/Statement/IncDecStatement.hpp"

void IncDecStatement::accept(Visitor& v) {
	//v.visit(this);
}

IncDecStatement::~IncDecStatement() {
	std::cout << "IncDecStatement destroyed" << std::endl;
}

#endif
