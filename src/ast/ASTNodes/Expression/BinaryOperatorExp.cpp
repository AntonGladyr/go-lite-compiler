#ifndef BINARYOPERATOREXP_CPP
#define BINARYOPERATOREXP_CPP

#include <sstream>
#include "AST/Expression/BinaryOperatorExp.hpp"

void BinaryOperatorExp::accept(Visitor& v) {
	//v.visit(this);
}

std::string BinaryOperatorExp::toString() {
	std::stringstream ss;
	ss << "(" << lhs->toString() <<	" " << op << " " << rhs->toString() << ")";
	return ss.str();
}

BinaryOperatorExp::~BinaryOperatorExp() {
	delete lhs;
	delete rhs;
	std::cout << "BinaryOperatorExp destroyed" << std::endl;
}

#endif
