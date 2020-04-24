#ifndef PROGRAM_CPP
#define PROGRAM_CPP

#include <iostream>
#include "AST/Program/Program.hpp"
#include "AST/Node.hpp"

void Program::accept(Visitor& v) {
	v.visit(this);
}

std::string Program::toString() {
	//TODO: fix declarations output
	std::stringstream ss;
	ss << "package " << package->name;
	return ss.str();
}

std::string Program::preambleToCcode() {
	std::stringstream ss;
	ss << "#include <stdio.h>" << std::endl
	   << "#include <string.h>" << std::endl << std::endl;
	
	return ss.str();
}
std::string Program::mainToCcode(
	const std::string &mainFuncCall,
	const std::string &initFuncCalls
) {
	std::stringstream ss;
	ss << "main() {" << std::endl
	   << initFuncCalls << std::endl
	   << mainFuncCall << std::endl
	   << "}" << std::endl;
	
	return ss.str();
}


Program::~Program() {
	delete package;
	
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
