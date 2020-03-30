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
			
			if (clause->first) {	
				if (clause->first->first) {	
					for(auto const& exp : *(clause->first->first)) {
						delete exp;
					}
					delete clause->first->first;
				}
					
				if (clause->first->second) {	
					delete clause->first->second;
				}	
				delete clause->first;	
			}
					
			delete clause;	
		}
		
		delete clauseList;
	}
	
	std::cout << "SwitchStatement destroyed" << std::endl;
}

#endif
