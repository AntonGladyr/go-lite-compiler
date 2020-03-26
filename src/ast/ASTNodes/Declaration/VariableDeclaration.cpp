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
	ss << "var " << idList << " ";

	if (!type.second.empty()) {	
		for(auto const& value: type.second) {
			ss << "[" << std::to_string(value) << "]";
		}	
	}

	ss << type.first;

	if (!expList.empty())
		ss << " = " << expList;
	ss << std::endl;
	return ss.str();
}


VariableDeclaration::~VariableDeclaration() {
	std::cout << "VariableDeclaration destroyed" << std::endl;
}

#endif
