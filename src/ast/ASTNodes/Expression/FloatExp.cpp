#ifndef FLOATEXP_CPP
#define FLOATEXP_CPP

#include <string>
#include "AST/Expression/FloatExp.hpp"

void FloatExp::accept(Visitor& v) {
	//v.visit(this);
}

std::string FloatExp::toString(){	
	return std::to_string(value);
}

FloatExp::~FloatExp() {	
	std::cout << "FloatExp destroyed" << std::endl;
}

#endif
