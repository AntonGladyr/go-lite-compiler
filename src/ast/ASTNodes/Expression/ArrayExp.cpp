#ifndef ARRAYEXP_CPP
#define ARRAYEXP_CPP

#include <sstream>
#include "ArrayExp.hpp"

void ArrayExp::accept(Visitor& v) {
	v.visit(this);
}

std::string ArrayExp::toString() {
	std::stringstream ss;
	ss << id;
	for(auto const& value: expList) {
		ss << "[" << value->toString() << "]";
	}
	return ss.str();
}

#endif
