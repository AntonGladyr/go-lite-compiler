#ifndef TYPE_DESCRIPTOR_CPP
#define TYPE_DESCRIPTOR_CPP

#include "TypeDescriptor/TypeDescriptor.hpp"

std::string TypeDescriptor::resolveNumericType(
	const std::string &lhsType, 
	const std::string &rhsType
) {
	// if both types are not float64
	if ( lhsType.compare(BASETYPE_FLOAT) != 0 &&
	     rhsType.compare(BASETYPE_FLOAT) != 0
	) return BASETYPE_INT;
	else return BASETYPE_FLOAT;
}

bool TypeDescriptor::isOrderedType() {
	return orderedTypesList.find(baseType) != orderedTypesList.end();
}

bool TypeDescriptor::isNumericType() {
	return numericTypesList.find(baseType) != numericTypesList.end();
}

bool TypeDescriptor::isIntegerType() {
	return integerTypesList.find(baseType) != integerTypesList.end();
}

bool TypeDescriptor::isStringType() {	
	return baseType.compare(BASETYPE_STRING) == 0;
}

bool TypeDescriptor::isBoolType() {	
	return baseType.compare(BASETYPE_BOOL) == 0;
}

bool TypeDescriptor::isBaseType() {	
	return baseTypesList.find(baseType) != baseTypesList.end();
}

#endif
