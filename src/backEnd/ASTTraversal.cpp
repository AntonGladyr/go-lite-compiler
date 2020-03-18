#ifndef ASTTRAVERSAL_CPP
#define ASTTRAVERSAL_CPP

#include <iostream>
#include <typeinfo>   // operator typeid
#include "ASTTraversal.hpp"
#include "Program.hpp"

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

	}

	//if (typeid(FuncDeclaration) == typeid(*node)) {
	//}
	
		//std::cout << "package " << ((Program*)node)->package << std::endl;
}

void ASTTraversal::clean(Node *node) {
	if (node == NULL) return;

	if (typeid(Program) == typeid(*node)) {
		Program *prg = (Program*)node;
		if (prg->declList) {
			for(auto decl : *(prg->declList)) {
				delete decl;
			}
		}
		
		
		delete prg->declList;
		delete prg;	
	}
}

#endif
