#ifndef DECLARATIONSTMT_CPP
#define DECLARATIONSTMT_CPP

#include <iostream> //delete
#include <string>
#include <sstream>
#include "AST/Statement/DeclarationStatement.hpp"
#include "../../../helpers/vectorExtension.cpp"

void DeclarationStatement::accept(Visitor& v) {
	v.visit(this);
}

std::string DeclarationStatement::toString() {
	std::stringstream ss;
	ss << decl->toString();
	return ss.str();
}

DeclarationStatement::~DeclarationStatement() {
	delete decl;
	std::cout << "DeclarationStatement destroyed" << std::endl;
}

#endif
