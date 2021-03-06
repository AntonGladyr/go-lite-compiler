#ifndef BLOCKSTMT_CPP
#define BLOCKSTMT_CPP

#include <sstream>
#include <iostream>
#include "AST/Statement/BlockStatement.hpp"

void BlockStatement::accept(Visitor& v) {
	v.visit(this);
}

std::string BlockStatement::toString() {
	std::stringstream ss;
	ss << "{" << std::endl;
	for(auto const& stmt : *stmtList) {
		ss << stmt->toString();
	}
	ss << "}"; 
	return ss.str();
}


BlockStatement::~BlockStatement() {
	if (stmtList) {	
		for(auto const& stmt : *stmtList) {	
			delete stmt;
		}
	}
	
	// for testing purposes
	// std::cout << "BlockStatement destroyed" << std::endl;
}

#endif
