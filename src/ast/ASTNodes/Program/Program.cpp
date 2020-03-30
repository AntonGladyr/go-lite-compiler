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
	//TODO: fix declarations output
	std::stringstream ss;
	ss << "package " << package; 
	return ss.str();
}

Program::~Program() {
	if (declList) {
		for(auto const& decl : *declList) {
			delete decl;
		}
		delete declList;
	}
	
	//for testing purposes
	//std::cout << "Program destroyed" << std::endl;
}

#endif
