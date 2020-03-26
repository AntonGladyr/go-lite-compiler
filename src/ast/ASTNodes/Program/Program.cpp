#ifndef PROGRAM_CPP
#define PROGRAM_CPP

#include <iostream>
#include <sstream>
#include "AST/Program/Program.hpp"
#include "AST/Node.hpp"

void Program::accept(Visitor& v) {
	v.visit(this);
}

std::string Program::toString() {
	std::stringstream ss;
	ss << "package " << package << std::endl;
	return ss.str();
}

Program::~Program() {
	std::cout << "Program destroyed" << std::endl;
}

#endif
