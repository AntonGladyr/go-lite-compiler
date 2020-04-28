#ifndef WEEDER_CPP
#define WEEDER_CPP

#include <sstream>
#include <iostream>
#include "Services/Weeder.hpp"
#include "AST/ASTTraversal.hpp"

void Weeder::weedOut(Program *prg) {
	program = prg;
	
	//traverse the AST
	ASTTraversal::traverse(prg, *this);
}

// termination after errors
void Weeder::terminate() {
	delete program;
	program = NULL;
	std::exit(EXIT_FAILURE);
}

void Weeder::visit(Program *prg) {
	if (prg == NULL) return;
}

void Weeder::visit(VariableDeclaration *varDecl) {
	if (varDecl == NULL) return;
}

void Weeder::visit(TypeDeclaration *typeDecl) {
	if (typeDecl == NULL) return;		
}

void Weeder::visit(FunctionDeclaration *funcDecl) {
	if (funcDecl == NULL) return;
}

void Weeder::visit(BlockStatement *blockStmt) {
	if (blockStmt == NULL) return;	
}

void Weeder::visit(DeclarationStatement *declStmt) {	
	if (declStmt == NULL) return;
}

void Weeder::visit(TypeDeclarationStatement *typeDeclStmt) {
	if (typeDeclStmt == NULL) return;
}

void Weeder::visit(AssignStatement *assignStmt) {
	if (assignStmt == NULL) return;
}

void Weeder::visit(ExpressionStatement *expStmt) {
	if (expStmt == NULL) return;
}

void Weeder::visit(ForStatement *forStmt) {
	if (forStmt == NULL) return;
}

void Weeder::visit(IfElseStatement *ifElseStmt) {	
	if (ifElseStmt == NULL) return;
	
	ASTTraversal::traverse(ifElseStmt->blockStmt, *this);
	
	if (ifElseStmt->ifStmt) {	
		ASTTraversal::traverse(ifElseStmt->ifStmt, *this);
	}
	
	if (ifElseStmt->elseBlockStmt ) {	
		ASTTraversal::traverse(ifElseStmt->elseBlockStmt, *this);
	}
}

void Weeder::visit(SwitchStatement *switchStmt) {
	if (switchStmt == NULL) return;
			
	numTabs++;
	if (switchStmt->clauseList) {	
		for(auto const& clause : *(switchStmt->clauseList)) {
			if (clause->clauseType == SWITCH_CLAUSE::CASE) {	
			}

			if (clause->clauseType == SWITCH_CLAUSE::DEFAULT) {		
			}
			
			if (clause->expList) {
			}	

			if (clause->blockStmt) {
				ASTTraversal::traverse(clause->blockStmt, *this);
			}	
		}
	}
	
	numTabs--;
}

void Weeder::visit(PrintStatement *printStmt) {
	if (printStmt == NULL) return;
}

void Weeder::visit(BreakStatement *breakStmt) {
	if (breakStmt == NULL) return;
}

void Weeder::visit(ContinueStatement *continueStmt) {
	if (continueStmt == NULL) return;
}

void Weeder::visit(IncDecStatement *incDecStmt) {
	if (incDecStmt == NULL) return;	
}

void Weeder::visit(ReturnStatement *returnStmt) {
	if (returnStmt == NULL) return;
}

void Weeder::visit(EmptyStatement *emptyStmt) {
	if (emptyStmt == NULL) return;
}

void Weeder::visit(ArrayExp *arrExp) {
	if (arrExp == NULL) return;
}

void Weeder::visit(BinaryOperatorExp *binOpExp) {
	if (binOpExp == NULL) return;
}

void Weeder::visit(BoolExp *boolExp) {
	if (boolExp == NULL) return;
}

void Weeder::visit(BuiltinsExp *builtinsExp) {
	if (builtinsExp == NULL) return;
}

void Weeder::visit(FloatExp *floatExp) {
	if (floatExp == NULL) return;
}

void Weeder::visit(FunctionCallExp *funcCallExp) {
	if (funcCallExp == NULL) return;
}

void Weeder::visit(IdentifierExp *idExp) {
	if (idExp == NULL) return;
}

void Weeder::visit(IntegerExp *intExp) {
	if (intExp == NULL) return;
}

void Weeder::visit(RuneExp *runeExp) {
	if (runeExp == NULL) return;
}

void Weeder::visit(StringExp *strExp) {
	if (strExp == NULL) return;
}

void Weeder::visit(UnaryExp *unaryExp) {
	if (unaryExp == NULL) return;
}

std::string Weeder::getTabs() {
}

#endif
