#ifndef BUILTINSEXP_CPP
#define BUILTINSEXP_CPP

#include <sstream>
#include "BuiltinsExp.hpp"

void BuiltinsExp::accept(Visitor& v) {
	v.visit(this);
}

std::string BuiltinsExp::toString() {
	std::stringstream ss;
	ss << name << "(" << exp->toString() << ")";
	return ss.str();
}

#endif
