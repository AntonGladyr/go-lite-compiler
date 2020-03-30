#ifndef VARDECL_CPP
#define VARDECL_CPP

#include <iostream> //delete
#include <string>
#include <sstream>
#include "AST/Declaration/VariableDeclaration.hpp"
#include "../../../helpers/vectorExtension.cpp"

void VariableDeclaration::accept(Visitor& v) {
	v.visit(this);
}

std::string VariableDeclaration::toString() {
	std::stringstream ss;	
	ss << "var " << *idList;

	if (type) {
		ss << " ";
		if (type->second) {	
			for(auto const& index : *(type->second)) {
				ss << "[" << std::to_string(index) << "]";
			}
		}
		
		ss << type->first;	
	}
		
	if (expList)
		ss << " = " << *expList;
		
	return ss.str();
}


VariableDeclaration::~VariableDeclaration() {
	for(auto const& id : *idList) {
		delete id;
	}
	delete idList;

	if (expList) {
		for(auto const& exp : *expList) {
			delete exp;
		}
		delete expList;
	}

	if (type) {
		if (type->second) delete type->second;
		delete type;
	}
	
	// for testing purposes	
	// std::cout << "VariableDeclaration destroyed" << std::endl;
}

#endif
