#ifndef TYPE_DESCRIPTOR_TABLE_CPP
#define TYPE_DESCRIPTOR_TABLE_CPP

#include "TypeDescriptorTable/TypeDescriptorTable.hpp"

void TypeDescriptorTable::append(
	std::string typeName,
	std::string targetTypeName	
) {
	typeTable.insert({typeName, targetTypeName});
}

std::string TypeDescriptorTable::getTypeDescriptor(std::string typeName) {
	// if key exists in the table return target type
	if ( typeTable.find(typeName) != typeTable.end() ) {
		return typeTable.find(typeName)->second;
	} else
	return std::string();
}

#endif
