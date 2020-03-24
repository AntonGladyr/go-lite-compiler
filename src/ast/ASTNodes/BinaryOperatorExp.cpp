#ifndef BINARYOPERATOREXP_CPP
#define BINARYOPERATOREXP_CPP

#include "BinaryOperatorExp.hpp"

void BinaryOperatorExp::accept(Visitor& v) {
	v.visit(this);
}

std::string BinaryOperatorExp::toString() {
	std::string res;
	res.append(lhs->toString());
	res.append(" ");
	res.append(op);
	res.append(" ");
	res.append(rhs->toString());
	return res;
}

#endif
