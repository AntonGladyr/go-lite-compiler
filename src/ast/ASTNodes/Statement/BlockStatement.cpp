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
	ss << "}" << std::endl;
	return ss.str();
}


BlockStatement::~BlockStatement() {
	for(auto const& stmt : *stmtList) {
		delete stmt;
	}
	std::cout << "BlockStatement destroyed" << std::endl;
}

#endif
