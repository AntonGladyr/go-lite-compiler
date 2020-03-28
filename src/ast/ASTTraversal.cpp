#ifndef ASTTRAVERSAL_CPP
#define ASTTRAVERSAL_CPP

#include <typeinfo>   // operator typeid
#include "AST/ASTTraversal.hpp"
#include "AST/Program/Program.hpp"
#include "AST/Declaration/VariableDeclaration.hpp"
#include "AST/Declaration/TypeDeclaration.hpp"
#include "AST/Declaration/FunctionDeclaration.hpp"
#include "AST/Statement/BlockStatement.hpp"
#include "AST/Statement/ReturnStatement.hpp"

void ASTTraversal::traverse(Node *node, Visitor& visitor) {
	if (node == NULL) return;
	if (typeid(Program) == typeid(*node)) {
		Program *prg = (Program*)node;
		prg->accept(visitor);
		if (prg->declList) {	
			for(auto const& decl : *(prg->declList)) {	
				traverse(decl, visitor);	
			}
		}
		
		return;
	}
	
	if (typeid(VariableDeclaration) == typeid(*node)) {
		VariableDeclaration *varDecl = (VariableDeclaration*)node;
		varDecl->accept(visitor);
	}

	if (typeid(TypeDeclaration) == typeid(*node)) {
		TypeDeclaration *typeDecl = (TypeDeclaration*)node;
		typeDecl->accept(visitor);	
	}

	if (typeid(FunctionDeclaration) == typeid(*node)) {
		FunctionDeclaration *funcDecl = (FunctionDeclaration*)node;
		funcDecl->accept(visitor);	
		traverse(funcDecl->blockStmt, visitor);
	}
	
	if (typeid(BlockStatement) == typeid(*node)) {	
		BlockStatement *blockStmt = (BlockStatement*)node;
		visitor.openScope();
		blockStmt->accept(visitor);
		for(auto const& stmt : *(blockStmt->stmtList)) {
			traverse(stmt, visitor);
		}
		visitor.closeScope();
		blockStmt->accept(visitor);
	}

	if (typeid(ReturnStatement) == typeid(*node)) {	
		ReturnStatement *returnStmt = (ReturnStatement*)node;
		returnStmt->accept(visitor);
	}

	if (typeid(EmptyStatement) == typeid(*node)) {
		EmptyStatement *emptyStmt = (EmptyStatement*)node;
		emptyStmt->accept(visitor);
	}
}

#endif
