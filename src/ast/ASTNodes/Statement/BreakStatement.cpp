#ifndef BREAKSTMT_CPP
#define BREAKSTMT_CPP

#include <iostream>
#include <sstream>
#include "AST/Statement/BreakStatement.hpp"

void BreakStatement::accept(Visitor& v) {
	v.visit(this);
}

std::string BreakStatement::toString() {
	std::stringstream ss;	
	ss << "break"; 
	return ss.str();
}


BreakStatement::~BreakStatement() {
	// for testing purposes
	// std::cout << "BreakStatement destroyed" << std::endl;
}

#endif
