#ifndef INCDECSTMT_CPP
#define INCDECSTMT_CPP

#include <iostream>
#include <sstream>
#include "AST/Statement/IncDecStatement.hpp"

void IncDecStatement::accept(Visitor& v) {
	v.visit(this);
}

std::string IncDecStatement::toString() {
	std::stringstream ss;
	ss << exp->toString() << (op == IncDecOp::INC ? "++" : "--");	
	return ss.str();
}

IncDecStatement::~IncDecStatement() {
	delete exp;
	std::cout << "IncDecStatement destroyed" << std::endl;
}

#endif
