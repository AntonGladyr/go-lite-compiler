#ifndef ASSIGNSTMT_CPP
#define ASSIGNSTMT_CPP

#include <iostream>
#include <sstream>
#include "AST/Statement/AssignStatement.hpp"
#include "../../../helpers/vectorExtension.cpp"

void AssignStatement::accept(Visitor& v) {
	v.visit(this);
}

std::string AssignStatement::toString() {
	std::stringstream ss;	
	ss << *lhs << " = " << *rhs;
	return ss.str();
}

AssignStatement::~AssignStatement() {
	for(auto const& exp : *lhs) {
		delete exp;
	}
	
	for(auto const& exp : *rhs) {
		delete exp;
	}

	delete lhs;
	delete rhs;
	std::cout << "AssignStatement destroyed" << std::endl;
}

#endif
