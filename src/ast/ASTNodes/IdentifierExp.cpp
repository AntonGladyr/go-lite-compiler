#ifndef IDENTIFIEREXP_CPP
#define IDENTIFIEREXP_CPP

#include <iostream>
#include "IdentifierExp.hpp"

void IdentifierExp::accept(Visitor& v) {
	v.visit(this);
}

std::string IdentifierExp::toString() {
	return value;
}

#endif
