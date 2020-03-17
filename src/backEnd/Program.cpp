#ifndef PROGRAM_CPP
#define PROGRAM_CPP

#include "Program.hpp"

void Program::accept(Visitor& v) {
	v.visit(this);
}

#endif
