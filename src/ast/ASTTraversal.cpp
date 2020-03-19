#ifndef ASTTRAVERSAL_CPP
#define ASTTRAVERSAL_CPP

#include <iostream>
#include <typeinfo>   // operator typeid
#include "ASTTraversal.hpp"
#include "Program.hpp"
#include "VariableDeclaration.hpp"

void ASTTraversal::traverse(Node *node, Visitor& visitor) {
	if (node == NULL) return;
	
	if (typeid(Program) == typeid(*node)) {
		Program *prg = (Program*)node;
		prg->accept(visitor);	
		if (prg->declList) {
			for(auto decl : *(prg->declList)) {	
				traverse(decl, visitor);
				//std::cout << "test" << std::endl;
				//decl->accept(this);
			}
		}
		
		return;
	}

	if (typeid(VariableDeclaration) == typeid(*node)) {
		VariableDeclaration *varDecl = (VariableDeclaration*)node;
		varDecl->accept(visitor);	
	}	
}

void ASTTraversal::clean(Node *node) {
	if (node == NULL) return;

	if (typeid(Program) == typeid(*node)) {
		Program *prg = (Program*)node;
		if (prg->declList) {
			for(auto decl : *(prg->declList)) {
				//TODO: destructors for Declaration and VariableDeclaration
				delete decl;
			}
		}
		
		
		delete prg->declList;
		delete prg;	
	}
}

#endif
