#ifndef EXPRESSIONSTMT_CPP
#define EXPRESSIONSTMT_CPP

#include <iostream>
#include <sstream>
#include "AST/Statement/ExpressionStatement.hpp"

void ExpressionStatement::accept(Visitor& v) {
	v.visit(this);
}

std::string ExpressionStatement::toString() {
	std::stringstream ss;	
	ss << exp->toString();
	return ss.str();
}

ExpressionStatement::~ExpressionStatement() {
	delete exp;

	// for testing purposes
	// std::cout << "ExpressionStatement destroyed" << std::endl;
}

#endif
