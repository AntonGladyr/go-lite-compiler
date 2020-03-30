#ifndef RETURNSTMT_CPP
#define RETURNSTMT_CPP

#include <sstream>
#include <iostream>
#include "AST/Statement/ReturnStatement.hpp"

void ReturnStatement::accept(Visitor& v) {
	v.visit(this);
}

std::string ReturnStatement::toString() {
	std::stringstream ss;	
	ss << "return";
	if (exp)
		ss << " " << exp->toString();
	return ss.str();
}


ReturnStatement::~ReturnStatement() {
	if (exp) delete exp;
	std::cout << "ReturnStatement destroyed" << std::endl;
}

#endif
