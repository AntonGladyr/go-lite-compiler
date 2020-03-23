#ifndef BOOLEXP_CPP
#define BOOLEXP_CPP

#include <string>
#include "BoolExp.hpp"

void BoolExp::accept(Visitor& v) {
	v.visit(this);
}

std::string BoolExp::toString() {
	return std::to_string(value);
}

#endif
