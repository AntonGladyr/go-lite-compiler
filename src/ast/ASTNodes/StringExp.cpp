#ifndef STRINGEXP_CPP
#define STRINGEXP_CPP

#include "StringExp.hpp"

void StringExp::accept(Visitor& v) {
	v.visit(this);
}

std::string StringExp::toString() {
	return value;
}

#endif
