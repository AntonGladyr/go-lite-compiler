#ifndef VARDECL_CPP
#define VARDECL_CPP

#include <iostream> //delete
#include <string>
#include <sstream>
#include "AST/Declaration/VariableDeclaration.hpp"
#include "../../../helpers/vectorExtension.cpp"
#include "SymbolTable/SymbolTable.hpp"

void VariableDeclaration::accept(Visitor& v) {
	v.visit(this);
}

std::string VariableDeclaration::toString() {
	std::stringstream ss;	
	ss << "var " << *idList;

	if (typeName) {
		ss << " ";
		if (typeName->indexes) {
			for(auto const& index : *(typeName->indexes)) {
				ss << "[" << std::to_string(index) << "]";
			}
		}
		
		ss << typeName->name;
	}
		
	if (expList)
		ss << " = " << *expList;
		
	return ss.str();
}

std::string VariableDeclaration::symbolToStr() { }

std::string VariableDeclaration::symbolTypeToStr() { }

VariableDeclaration::VariableDeclaration(
	std::vector<IdentifierExp*> *_idList,
	std::vector<Expression*> *_expList,
	int _lineno
) : idList(_idList), expList(_expList), Declaration(_lineno) {
	for(auto const& id : *idList) {
		id->parentNode = this;
	}		
}
		
VariableDeclaration::VariableDeclaration(
	std::vector<IdentifierExp*> *_idList,
	TypeName *_typeName,
	std::vector<Expression*> *_expList,
	int _lineno
) : idList(_idList), typeName(_typeName), expList(_expList), Declaration(_lineno) {
	for(auto const& id : *idList) {
		id->parentNode = this;
	}
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

	if (typeName) delete typeName;
	
	// for testing purposes	
	// std::cout << "VariableDeclaration destroyed" << std::endl;
}

#endif
