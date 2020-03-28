#ifndef BOOLEXP_CPP
#define BOOLEXP_CPP

#include <string>
#include "AST/Expression/BoolExp.hpp"

void BoolExp::accept(Visitor& v) {
	//v.visit(this);
}

std::string BoolExp::toString() {	
	std::string boolVal = (value) ? "true" : "false";	
	return boolVal;
}

BoolExp::~BoolExp() {	
	std::cout << "BoolExp destroyed" << std::endl;
}

#endif
