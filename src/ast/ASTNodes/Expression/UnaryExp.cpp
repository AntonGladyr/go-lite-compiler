#ifndef UNARYEXP_CPP
#define UNARYEXP_CPP

#include <sstream>
#include "AST/Expression/UnaryExp.hpp"

void UnaryExp::accept(Visitor& v) {
	v.visit(this);
}

std::string UnaryExp::toString() {
	std::stringstream ss;
	ss << op << "(" << exp->toString() << ")";
	return ss.str();
}

UnaryExp::~UnaryExp() {
	delete exp;
	
	// for testing purposes
	// std::cout << "UnaryExp destroyed" << std::endl;
}

#endif
