#ifndef FUNCTIONCALLEXP_CPP
#define FUNCTIONCALLEXP_CPP

#include <sstream>
#include "FunctionCallExp.hpp"
#include "../../../helpers/vectorExtension.cpp"

void FunctionCallExp::accept(Visitor& v) {
	v.visit(this);
}

std::string FunctionCallExp::toString() {
	std::stringstream ss;
	ss << exp->toString() << "(" << expList << ")";
	return ss.str();
}

#endif
