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
			
			if (param->type) {
				if (param->type->indexes) {
					for(auto const& index : *(param->type->indexes)) {
						ss << "[" << std::to_string(index) << "]";
					}
				}
				
				ss << param->type->name;
				if (&param != &params->back())
					ss << ", ";
			}
			
		}
	}
	
	ss << ") ";
	
	//function type
	//indexes	
	if (type) {
		if (type->indexes) {
			for(auto const& index : *(type->indexes)) {
				ss << "[" << std::to_string(index) << "]";
			}	
		}	
		//type name
		ss << type->name << " ";
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
	
	if (type) {
		// array indexes
		if (type->indexes) {	
			for(auto const& index : *(type->indexes)) {
				ss << "[" << std::to_string(index) << "]";
			}	
		}	
		// type id
		ss << type->name;
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
			if (param->type->indexes) {
				for(auto const& index : *(param->type->indexes)) {
					ss << "[" << std::to_string(index) << "]";
				}	
			}
			
			ss << param->type->name;
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

	if (type) delete type;
	
	delete blockStmt;
	
	// for testing purposes
	// std::cout << "FunctionDeclaration destroyed" << std::endl;
}

#endif
