#ifndef STRINGEXP_CPP
#define STRINGEXP_CPP

#include <iostream>
#include "StringExp.hpp"

void StringExp::accept(Visitor& v) {
	v.visit(this);
}


std::ostream& StringExp::toString(std::ostream& o) const {
	return o << value;
}

#endif
