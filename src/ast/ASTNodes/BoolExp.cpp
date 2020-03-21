#ifndef BOOLEXP_CPP
#define BOOLEXP_CPP

#include <iostream>
#include "BoolExp.hpp"

void BoolExp::accept(Visitor& v) {
	v.visit(this);
}

std::ostream& BoolExp::toString(std::ostream& o) const {
	return o << value;
}

#endif
