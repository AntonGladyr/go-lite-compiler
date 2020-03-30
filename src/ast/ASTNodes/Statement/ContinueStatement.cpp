#ifndef CONTINUESTMT_CPP
#define CONTINUESTMT_CPP

#include <iostream>
#include <sstream>
#include "AST/Statement/ContinueStatement.hpp"

void ContinueStatement::accept(Visitor& v) {
	v.visit(this);
}

std::string ContinueStatement::toString() {
	std::stringstream ss;	
	ss << "continue"; 
	return ss.str();
}


ContinueStatement::~ContinueStatement() {
	// for testing purposes
	//std::cout << "ContinueStatement destroyed" << std::endl;
}

#endif
