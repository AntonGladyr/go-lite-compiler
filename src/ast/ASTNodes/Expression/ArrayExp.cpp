#ifndef ARRAYEXP_CPP
#define ARRAYEXP_CPP

#include <sstream>
#include "AST/Expression/ArrayExp.hpp"

void ArrayExp::accept(Visitor& v) {
	v.visit(this);
}

std::string ArrayExp::toString() {
	std::stringstream ss;
	ss << idExp->id;
	for(auto const& exp: *expList) {
		ss << "[" << exp->toString() << "]";
	}
	return ss.str();
}

ArrayExp::~ArrayExp() {
	delete idExp;

	for(auto const& exp: *expList) {
		delete exp;
	}
	
	// for testing purposes
	// std::cout << "ArrayExp destroyed" << std::endl;
}

#endif
