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
	ss << "type " << idExp->name << " ";
	if (typeName->indexes) {
		for(auto const& index: *(typeName->indexes)) {
			ss << "[" << std::to_string(index) << "]";
		}
	}
	
	ss << typeName->name;
	
	return ss.str();
}

std::string TypeDeclaration::symbolToStr() {
	std::stringstream ss;
	ss << idExp->name << " [" << CATEGORY_TYPE << "]" << " = ";
	ss << idExp->name << " -> ";
	ss << symbolTypeToStr();
	return ss.str();
}

std::string TypeDeclaration::symbolTypeToStr() {
	std::stringstream ss;	
	if (typeName->indexes) {
		for(auto const& index: *(typeName->indexes)) {
			ss << "[" << std::to_string(index) << "]";
		}
	}
	ss << typeName->name;
	return ss.str();
}

TypeDeclaration::~TypeDeclaration() {
	delete idExp;	
	
	delete typeName;
	
	// for testing purposes
	// std::cout << "TypeDeclaration destroyed" << std::endl;
}

#endif
