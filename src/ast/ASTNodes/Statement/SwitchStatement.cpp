#ifndef SWITCHSTMT_CPP
#define SWITCHSTMT_CPP

#include <sstream>
#include <iostream>
#include "AST/Statement/SwitchStatement.hpp"

void SwitchStatement::accept(Visitor& v) {
	v.visit(this);
}

std::string SwitchStatement::toString() {
	//TODO: implement method
	std::stringstream ss;	
	return ss.str();
}


SwitchStatement::~SwitchStatement() {
	if(exp) delete exp;	
	if (clauseList) {	
		for(auto const& clause : *clauseList) {		
			delete clause;	
		}	
		delete clauseList;	
	}	
	// for testing purposes	
	// std::cout << "SwitchStatement destroyed" << std::endl;
}

#endif
