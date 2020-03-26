#ifndef PRINTSTMT_CPP
#define PRINTSTMT_CPP

#include <iostream>
#include "AST/Statement/PrintStatement.hpp"

void PrintStatement::accept(Visitor& v) {
	//v.visit(this);
}

PrintStatement::~PrintStatement() {
	std::cout << "PrintStatement destroyed" << std::endl;
}

#endif
