#ifndef SWITCHSTMT_CPP
#define SWITCHSTMT_CPP

#include <iostream>
#include "AST/Statement/SwitchStatement.hpp"

void SwitchStatement::accept(Visitor& v) {
	//v.visit(this);
}

SwitchStatement::~SwitchStatement() {
	std::cout << "SwitchStatement destroyed" << std::endl;
}

#endif
