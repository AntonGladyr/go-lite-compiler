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

	//TODO: fix block output
	ss << "func " << id;
	ss << "(";
	
	//parameters	
	if (params) {
		for(auto const& param : *params) {
			ss << param->first << " ";
				
			if (param->second->second) {
				for(auto const& index : *(param->second->second)) {
					ss << "[" << std::to_string(index) << "]";
				}	
			}
			
			ss << param->second->first;
			if (&param != &params->back())
				ss << ", ";
		}
	}
	
	ss << ") ";
	
	//function type
	//indexes	
	if (type) {
		if (type->second) {	
			for(auto const& index : *(type->second)) {
				ss << "[" << std::to_string(index) << "]";
			}	
		}	
		//type id
		ss << type->first << " ";	
	}

	return ss.str();
}

std::string FunctionDeclaration::symbolToStr() {
	std::stringstream ss;
	ss << id << " [" << CATEGORY_FUNC << "]" << " = ";
	ss << symbolSignatureToStr();
	return ss.str();
}

std::string FunctionDeclaration::symbolTypeToStr() {
	std::stringstream ss;
	
	if (type) {
		// array indexes
		if (type->second) {	
			for(auto const& index : *(type->second)) {
				ss << "[" << std::to_string(index) << "]";
			}	
		}	
		// type id
		ss << type->first;
	} else {
		ss << "void";
	}

	return ss.str();
}

std::string FunctionDeclaration::symbolSignatureToStr() {
	std::stringstream ss;
	
	// params
	ss << "(";
	if (params) {
		for(auto const& param : *params) {
			// for each id print type
			if (param->second->second) {
				for(auto const& index : *(param->second->second)) {
					ss << "[" << std::to_string(index) << "]";
				}	
			}
			
			ss << param->second->first;
			if (&param != &params->back())
				ss << ", ";
		}

	}
	ss << ")";
	
	ss << " -> ";

	ss << symbolTypeToStr();

	return ss.str();
}

FunctionDeclaration::~FunctionDeclaration() {
	if (params) {
		for(auto const& param : *params) {
			delete param->second->second;
			delete param->second;
			delete param;
		}
		delete params;
	}

	if (type) {
		if (type->second) delete type->second;
		delete type;
	}
	
	delete blockStmt;
	
	// for testing purposes
	// std::cout << "FunctionDeclaration destroyed" << std::endl;
}

#endif
