#ifndef IDENTIFIEREXP_CPP
#define IDENTIFIEREXP_CPP

#include "AST/Expression/IdentifierExp.hpp"

void IdentifierExp::accept(Visitor& v) {
	v.visit(this);
}

std::string IdentifierExp::toString() {
	return id;
}

IdentifierExp::~IdentifierExp() {
	// for testing purposes
	// std::cout << "IdentifierExp destroyed" << std::endl;
}

#endif
