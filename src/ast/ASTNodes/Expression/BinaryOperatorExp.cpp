#ifndef BINARYOPERATOREXP_CPP
#define BINARYOPERATOREXP_CPP

#include <sstream>
#include "AST/Expression/BinaryOperatorExp.hpp"

void BinaryOperatorExp::accept(Visitor& v) {
	v.visit(this);
}

bool BinaryOperatorExp::isIntegerOperator() {
	return integerOpList.find(op) != integerOpList.end();
}

bool BinaryOperatorExp::isNumericOperator() {
	return numericOpList.find(op) != numericOpList.end();
}

bool BinaryOperatorExp::isOrderedOperator() {
	return orderedOpList.find(op) != orderedOpList.end();
}

bool BinaryOperatorExp::isBoolOperator() {
	return boolOpList.find(op) != boolOpList.end();
}

bool BinaryOperatorExp::isComparableOperator() {
	return comparableOpList.find(op) != comparableOpList.end();
}

std::string BinaryOperatorExp::toString() {
	std::stringstream ss;
	ss << "(" << lhs->toString() <<	" " << op << " " << rhs->toString() << ")";
	return ss.str();
}

BinaryOperatorExp::~BinaryOperatorExp() {
	delete lhs;
	delete rhs;
	
	// for testing purposes
	// std::cout << "BinaryOperatorExp destroyed" << std::endl;
}

#endif
