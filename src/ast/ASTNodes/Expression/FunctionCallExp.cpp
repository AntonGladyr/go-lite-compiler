#ifndef FUNCTIONCALLEXP_CPP
#define FUNCTIONCALLEXP_CPP

#include <sstream>
#include "AST/Expression/FunctionCallExp.hpp"
#include "../../../helpers/vectorExtension.cpp"

void FunctionCallExp::accept(Visitor& v) {
	v.visit(this);
}

std::string FunctionCallExp::toString() {
	std::stringstream ss;
	ss << exp->toString() << "(" << expList << ")";
	return ss.str();
}

FunctionCallExp::~FunctionCallExp() {
	delete exp;
	for(auto const& exp : *expList) {
		delete exp;
	}
	
	// for testing purposes
	// std::cout << "FunctionCallExp destroyed" << std::endl;
}

#endif
