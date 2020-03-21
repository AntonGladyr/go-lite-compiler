#ifndef FLOATEXP_CPP
#define FLOATEXP_CPP

#include <iostream>
#include "FloatExp.hpp"

void FloatExp::accept(Visitor& v) {
	v.visit(this);
}

std::ostream& FloatExp::toString(std::ostream& o) const {
	return o << value;
}

#endif
