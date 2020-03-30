#ifndef TYPEDECLSTMT_CPP
#define TYPEDECLSTMT_CPP

#include <iostream> //delete
#include <string>
#include <sstream>
#include "AST/Statement/TypeDeclarationStatement.hpp"

void TypeDeclarationStatement::accept(Visitor& v) {
	v.visit(this);
}

std::string TypeDeclarationStatement::toString() {
	std::stringstream ss;	
	ss << typeDecl->toString();
	return ss.str();
}


TypeDeclarationStatement::~TypeDeclarationStatement() {	
	delete typeDecl;
	std::cout << "TypeDeclarationStatement destroyed" << std::endl;
}

#endif
