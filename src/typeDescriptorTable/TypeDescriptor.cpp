#ifndef TYPE_DESCRIPTOR_CPP
#define TYPE_DESCRIPTOR_CPP

#include <iostream>
#include "TypeDescriptorTable/TypeDescriptor.hpp"

bool TypeDescriptor::isComparableType() {
	return false;
}

bool TypeDescriptor::isOrderedType() {
}

bool TypeDescriptor::isNumericType() {
	return numericTypesList.find(baseType) != numericTypesList.end();
}

bool TypeDescriptor::isIntegerType() {
	return integerTypesList.find(baseType) != integerTypesList.end();
}

bool TypeDescriptor::isStringType() {
	return false;
}

bool TypeDescriptor::isBoolType() {
	return false;
}

#endif
