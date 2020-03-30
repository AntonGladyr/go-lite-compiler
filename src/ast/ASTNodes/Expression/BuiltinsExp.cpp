#ifndef BUILTINSEXP_CPP
#define BUILTINSEXP_CPP

#include <sstream>
#include "AST/Expression/BuiltinsExp.hpp"

void BuiltinsExp::accept(Visitor& v) {
	//v.visit(this);
}

std::string BuiltinsExp::toString() {
	std::stringstream ss;
	ss << name << "(" << exp->toString() << ")";
	return ss.str();
}

BuiltinsExp::~BuiltinsExp() {
	delete exp;

	// for testing purposes
	// std::cout << "BuiltinsExp destroyed" << std::endl;
}

#endif
