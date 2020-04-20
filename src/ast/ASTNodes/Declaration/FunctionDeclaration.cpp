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
	ss << "func " << idExp->name;
	ss << "(";
	
	//parameters	
	if (params) {
		for(auto const& param : *params) {
			ss << param->idExp->name << " ";
			
			if (param->typeName) {
				if (param->typeName->indexes) {
					for(auto const& index : *(param->typeName->indexes)) {
						ss << "[" << std::to_string(index) << "]";
					}
				}
				
				ss << param->typeName->name;
				if (&param != &params->back())
					ss << ", ";
			}
			
		}
	}
	
	ss << ") ";
	
	//function type
	//indexes	
	if (typeName) {
		if (typeName->indexes) {
			for(auto const& index : *(typeName->indexes)) {
				ss << "[" << std::to_string(index) << "]";
			}	
		}	
		//type name
		ss << typeName->name << " ";
	}

	return ss.str();
}

std::string FunctionDeclaration::symbolToStr() {
	std::stringstream ss;
	ss << idExp->name << " [" << CATEGORY_FUNC << "]" << " = ";
	ss << symbolSignatureToStr();
	return ss.str();
}

std::string FunctionDeclaration::symbolTypeToStr() {
	std::stringstream ss;
	
	if (typeName) {
		// array indexes
		if (typeName->indexes) {	
			for(auto const& index : *(typeName->indexes)) {
				ss << "[" << std::to_string(index) << "]";
			}	
		}	
		// type id
		ss << typeName->name;
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
			if (param->typeName->indexes) {
				for(auto const& index : *(param->typeName->indexes)) {
					ss << "[" << std::to_string(index) << "]";
				}	
			}
			
			ss << param->typeName->name;
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
	delete idExp;

	if (params) {
		for(auto const& param : *params) {
			delete param;
		}
		delete params;
	}

	if (typeName) delete typeName;
	
	delete blockStmt;
	
	// for testing purposes
	// std::cout << "FunctionDeclaration destroyed" << std::endl;
}

#endif
