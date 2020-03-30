#ifndef PRINTSTMT_CPP
#define PRINTSTMT_CPP

#include <iostream>
#include <sstream>
#include "AST/Statement/PrintStatement.hpp"
#include "../../../helpers/vectorExtension.cpp"

void PrintStatement::accept(Visitor& v) {
	v.visit(this);
}

std::string PrintStatement::toString() {
	std::stringstream ss;	
	ss << "print(" << *expList << ")"; 
	return ss.str();
}

PrintStatement::~PrintStatement() {
	for(auto const& exp : *expList) {
		delete exp;
	}
	delete expList;
	
	// for testing purposes
	// std::cout << "PrintStatement destroyed" << std::endl;
}

#endif
