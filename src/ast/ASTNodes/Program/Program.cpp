#ifndef PROGRAM_CPP
#define PROGRAM_CPP

#include <iostream>
#include "Program.hpp"
#include "Node.hpp"

void Program::accept(Visitor& v) {
	v.visit(this);
}

Program::~Program() {
	std::cout << "Program destroyed" << std::endl;
}

#endif
