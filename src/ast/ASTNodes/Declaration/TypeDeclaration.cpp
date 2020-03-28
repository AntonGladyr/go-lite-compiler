#ifndef TYPEDECL_CPP
#define TYPEDECL_CPP

#include <iostream> //delete
#include <string>
#include <sstream>
#include "AST/Declaration/TypeDeclaration.hpp"


void TypeDeclaration::accept(Visitor& v) {
	v.visit(this);
}

std::string TypeDeclaration::toString() {
	std::stringstream ss;	
	ss << "type " << id << " ";
	if (type->second) {
		for(auto const& index: *(type->second)) {
			ss << "[" << std::to_string(index) << "]";
		}
	}
	
	ss << type->first;
	
	ss << std::endl;
	return ss.str();
}


TypeDeclaration::~TypeDeclaration() {
	if (type->second) delete type->second;
	
	delete type;
	std::cout << "TypeDeclaration destroyed" << std::endl;
}

#endif
