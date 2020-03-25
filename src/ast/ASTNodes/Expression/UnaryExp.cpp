#ifndef UNARYEXP_CPP
#define UNARYEXP_CPP

#include <sstream>
#include "UnaryExp.hpp"

void UnaryExp::accept(Visitor& v) {
	v.visit(this);
}

std::string UnaryExp::toString() {
	std::stringstream ss;
	ss << op << "(" << exp->toString() << ")";
	return ss.str();
}

#endif
