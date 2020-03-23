#ifndef INTEGEREXP_CPP
#define INTEGEREXP_CPP

#include <string>
#include "IntegerExp.hpp"

void IntegerExp::accept(Visitor& v) {
	v.visit(this);
}

std::string IntegerExp::toString() {
	return std::to_string(value);
}

#endif
