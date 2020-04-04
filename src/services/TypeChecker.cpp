#ifndef TYPECHECKER_CPP
#define TYPECHECKER_CPP

#include <sstream>
#include <iostream>
#include "Services/TypeChecker.hpp"
#include "AST/ASTTraversal.hpp"

void TypeChecker::typecheck(Program *prg, SymbolTable *symbolTable) {
	this->symbolTable = symbolTable;
}

void TypeChecker::visit(Program *prg) {
	if (prg == NULL) return;
}

void TypeChecker::visit(VariableDeclaration *varDecl) {
	if (varDecl == NULL) return;	
}

void TypeChecker::visit(TypeDeclaration *typeDecl) {
	if (typeDecl == NULL) return;		
}

void TypeChecker::visit(FunctionDeclaration *funcDecl) {
	if (funcDecl == NULL) return;	
}

void TypeChecker::visit(BlockStatement *blockStmt) {
	if (blockStmt == NULL) return;
	
	/*if (isScopeOpened) {
		
	} else {
		
		
	}*/
}

void TypeChecker::visit(DeclarationStatement *declStmt) {	
	if (declStmt == NULL) return;	
}

void TypeChecker::visit(TypeDeclarationStatement *typeDeclStmt) {
	if (typeDeclStmt == NULL) return;	
}

void TypeChecker::visit(AssignStatement *assignStmt) {
	if (assignStmt == NULL) return;	
}

void TypeChecker::visit(ExpressionStatement *expStmt) {
	if (expStmt == NULL) return;	
}

void TypeChecker::visit(ForStatement *forStmt) {
	if (forStmt == NULL) return;	
}

void TypeChecker::visit(IfElseStatement *ifElseStmt) {	
	if (ifElseStmt == NULL) return;
		
	ASTTraversal::traverse(ifElseStmt->blockStmt, *this);
	
	if (ifElseStmt->ifStmt) {	
		ASTTraversal::traverse(ifElseStmt->ifStmt, *this);
	}
	
	if (ifElseStmt->elseBlockStmt ) {	
		ASTTraversal::traverse(ifElseStmt->elseBlockStmt, *this);
	}
}

void TypeChecker::visit(SwitchStatement *switchStmt) {
	if (switchStmt == NULL) return;
		
	//if (switchStmt->exp) std::cout << " " << switchStmt->exp->toString();
		
	if (switchStmt->clauseList) {	
		for(auto const& clause : *(switchStmt->clauseList)) {	
			if (clause->first) {
				if (clause->first->first) {
					// case expressions	
				}

				if (clause->first->second) {
					// case/default block
					ASTTraversal::traverse(clause->first->second, *this);
				}
			}
		}
	}
}

void TypeChecker::visit(PrintStatement *printStmt) {
	if (printStmt == NULL) return;	
}

void TypeChecker::visit(BreakStatement *breakStmt) {
	if (breakStmt == NULL) return;	
}

void TypeChecker::visit(ContinueStatement *continueStmt) {
	if (continueStmt == NULL) return;
}

void TypeChecker::visit(IncDecStatement *incDecStmt) {
	if (incDecStmt == NULL) return;	
}

void TypeChecker::visit(ReturnStatement *returnStmt) {
	if (returnStmt == NULL) return;
}

void TypeChecker::visit(EmptyStatement *emptyStmt) {
	if (emptyStmt == NULL) return;	
}

void TypeChecker::visit(ArrayExp *arrExp) {
	if (arrExp == NULL) return;
}

void TypeChecker::visit(BinaryOperatorExp *binOpExp) {
	if (binOpExp == NULL) return;
}

void TypeChecker::visit(BoolExp *boolExp) {
	if (boolExp == NULL) return;
}

void TypeChecker::visit(BuiltinsExp *builtinsExp) {
	if (builtinsExp == NULL) return;
}

void TypeChecker::visit(FloatExp *floatExp) {
	if (floatExp == NULL) return;
}

void TypeChecker::visit(FunctionCallExp *funcCallExp) {
	if (funcCallExp == NULL) return;
}

void TypeChecker::visit(IdentifierExp *idExp) {
	if (idExp == NULL) return;
}

void TypeChecker::visit(IntegerExp *intExp) {
	if (intExp == NULL) return;
}

void TypeChecker::visit(RuneExp *runeExp) {
	if (runeExp == NULL) return;
}

void TypeChecker::visit(StringExp *strExp) {
	if (strExp == NULL) return;
}

void TypeChecker::visit(UnaryExp *unaryExp) {
	if (unaryExp == NULL) return;
}

#endif
