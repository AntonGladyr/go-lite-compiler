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
	
	return ss.str();
}

std::string TypeDeclaration::symbolToStr() {
	std::stringstream ss;
	ss << id << " [" << CATEGORY_TYPE << "]" << " = ";
	ss << id << " -> ";
	ss << symbolTypeToStr();
	return ss.str();
}

std::string TypeDeclaration::symbolTypeToStr() {
	std::stringstream ss;	
	if (type->second) {
		for(auto const& index: *(type->second)) {
			ss << "[" << std::to_string(index) << "]";
		}
	}
	ss << type->first;
	return ss.str();
}

TypeDeclaration::~TypeDeclaration() {
	if (type->second) delete type->second;
	
	delete type;
	
	// for testing purposes
	// std::cout << "TypeDeclaration destroyed" << std::endl;
}

#endif
