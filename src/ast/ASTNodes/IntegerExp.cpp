#ifndef INTEGEREXP_CPP
#define INTEGEREXP_CPP

#include <iostream>
#include "IntegerExp.hpp"

void IntegerExp::accept(Visitor& v) {
	v.visit(this);
}

std::ostream& IntegerExp::toString(std::ostream& o) const {
	return o << value;
}

#endif
