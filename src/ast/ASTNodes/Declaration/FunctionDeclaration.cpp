#ifndef FUNCDECL_CPP
#define FUNCDECL_CPP

#include <iostream> //delete
#include <string>
#include <sstream>
#include "AST/Declaration/FunctionDeclaration.hpp"


void FunctionDeclaration::accept(Visitor& v) {
	v.visit(this);
}

std::string FunctionDeclaration::toString() {
	std::stringstream ss;	
	ss << "func " << id;
	ss << "(";
	
	//parameters
	if (!params->empty()) {
		for(auto const& param : *params) {	
			ss << param.first << " ";
			
			if (!param.second.second.empty()) {
				for(auto const& value : param.second.second) {
					ss << "[" << std::to_string(value) << "]";
				}	
			}
			
			ss << param.second.first;
			if (&param != &params->back())
				ss << ", ";
		}
	}
	
	ss << ") ";
	
	//function type
	//indexes	
	if (!type.second.empty()) {	
		for(auto const& value : type.second) {
			ss << "[" << std::to_string(value) << "]";
		}	
	}
	
	//type id
	if (!type.first.empty())
		ss << type.first << " ";	

	return ss.str();
}


FunctionDeclaration::~FunctionDeclaration() {
	std::cout << "FunctionDeclaration destroyed" << std::endl;
}

#endif
