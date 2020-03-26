#ifndef ASTTRAVERSAL_CPP
#define ASTTRAVERSAL_CPP

#include <typeinfo>   // operator typeid
#include "AST/ASTTraversal.hpp"
#include "AST/Program/Program.hpp"
#include "AST/Declaration/VariableDeclaration.hpp"
#include "AST/Declaration/TypeDeclaration.hpp"
#include "AST/Declaration/FunctionDeclaration.hpp"
#include "AST/Statement/Statement.hpp"

void ASTTraversal::traverse(Node *node, Visitor& visitor) {
	if (node == NULL) return;
	
	if (typeid(Program) == typeid(*node)) {
		Program *prg = (Program*)node;
		prg->accept(visitor);	
		if (prg->declList) {
			for(auto decl : *(prg->declList)) {	
				traverse(decl, visitor);	
			}
		}
		
		return;
	}
	
	if (typeid(VariableDeclaration) == typeid(*node)) {	
		VariableDeclaration *varDecl = (VariableDeclaration*)node;
		varDecl->accept(visitor);
	}

	/*if (typeid(TypeDeclaration) == typeid(*node)) {
		TypeDeclaration *typeDecl = (TypeDeclaration*)node;
		typeDecl->accept(visitor);	
	}

	if (typeid(FunctionDeclaration) == typeid(*node)) {
		FunctionDeclaration *funcDecl = (FunctionDeclaration*)node;
		funcDecl->accept(visitor);
		//traverse(blockstmt);
	}*/
	
	if (typeid(Statement) == typeid(*node)) {
		Statement *stmt = (Statement*)node;
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
