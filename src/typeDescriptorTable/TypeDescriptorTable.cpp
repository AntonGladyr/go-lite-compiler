#ifndef TYPE_DESCRIPTOR_TABLE_CPP
#define TYPE_DESCRIPTOR_TABLE_CPP

#include "TypeDescriptorTable/TypeDescriptorTable.hpp"

void TypeDescriptorTable::append(
	std::string typeName,
	std::string category,
	std::string baseType,
	std::string baseTypeCategory,
	Node *node
) {
	/*TypeDescriptor baseTypeDescriptor = TypeDescriptor(
						baseType,
						baseTypeCategory,
						NULL,
						NULL
					);
	TypeDescriptor typeDescriptor = TypeDescriptor(
						typeName,
						category,
						baseTypeDescriptor,
						node
					);
	typeTable.insert({typeName, typeDescriptor});*/
}

TypeDescriptor TypeDescriptorTable::getTypeDescriptor(std::string typeName) {
	// if key exists in the table return descriptor (value)
	if ( typeTable.find(typeName) != typeTable.end() ) {
		return typeTable.find(typeName)->second;
	} else {
		// return NULL if key does not exist
		//return NULL;
	}
}

#endif
