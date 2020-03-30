#ifndef INTEGEREXP_CPP
#define INTEGEREXP_CPP

#include <string>
#include "AST/Expression/IntegerExp.hpp"

void IntegerExp::accept(Visitor& v) {
	//v.visit(this);
}

std::string IntegerExp::toString() {
	return std::to_string(value);	
}

IntegerExp::~IntegerExp() {
	// for testing purposes
	//std::cout << "IntegerExp destroyed" << std::endl;
}

#endif
