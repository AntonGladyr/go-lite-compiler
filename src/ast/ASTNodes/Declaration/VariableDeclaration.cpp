#ifndef VARDECL_CPP
#define VARDECL_CPP

#include <iostream>
#include "VariableDeclaration.hpp"

void VariableDeclaration::accept(Visitor& v) {
	v.visit(this);
}

VariableDeclaration::~VariableDeclaration() {
	std::cout << "VariableDeclaration destroyed" << std::endl;
}

#endif
