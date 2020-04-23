#ifndef CODE_GENERATOR_CPP
#define CODE_GENERATOR_CPP

#include <sstream>
#include <iostream>
#include "Services/CodeGenerator.hpp"
#include "AST/ASTTraversal.hpp"

void CodeGenerator::emit(Program *prg, SymbolTable *st) {
	symbolTable = st;
	ASTTraversal::traverse(prg, *this);
}

void CodeGenerator::visit(Program *prg) {
	if (prg == NULL) return;
	std::cout << "hello" << std::endl;
	//TODO: collect all init functions
}

void CodeGenerator::visit(VariableDeclaration *varDecl) {
	if (varDecl == NULL) return;	
}

void CodeGenerator::visit(TypeDeclaration *typeDecl) {
	if (typeDecl == NULL) return;		
}

void CodeGenerator::visit(FunctionDeclaration *funcDecl) {
	if (funcDecl == NULL) return;	
}

void CodeGenerator::visit(BlockStatement *blockStmt) {
	if (blockStmt == NULL) return;
	
	/*if (isScopeOpened) {
		
	} else {
		
		
	}*/
}

void CodeGenerator::visit(DeclarationStatement *declStmt) {	
	if (declStmt == NULL) return;	
}

void CodeGenerator::visit(TypeDeclarationStatement *typeDeclStmt) {
	if (typeDeclStmt == NULL) return;	
}

void CodeGenerator::visit(AssignStatement *assignStmt) {
	if (assignStmt == NULL) return;	
}

void CodeGenerator::visit(ExpressionStatement *expStmt) {
	if (expStmt == NULL) return;	
}

void CodeGenerator::visit(ForStatement *forStmt) {
	if (forStmt == NULL) return;	
}

void CodeGenerator::visit(IfElseStatement *ifElseStmt) {	
	if (ifElseStmt == NULL) return;
		
	ASTTraversal::traverse(ifElseStmt->blockStmt, *this);
	
	if (ifElseStmt->ifStmt) {	
		ASTTraversal::traverse(ifElseStmt->ifStmt, *this);
	}
	
	if (ifElseStmt->elseBlockStmt ) {	
		ASTTraversal::traverse(ifElseStmt->elseBlockStmt, *this);
	}
}

void CodeGenerator::visit(SwitchStatement *switchStmt) {
	if (switchStmt == NULL) return;
		
	//if (switchStmt->exp) std::cout << " " << switchStmt->exp->toString();
		
	if (switchStmt->clauseList) {	
		for(auto const& clause : *(switchStmt->clauseList)) {	
			if (clause->expList) {
				// case expressions
			}

			if (clause->blockStmt) {
				// case/default block statement
				ASTTraversal::traverse(clause->blockStmt, *this);
			}
		}
	}
}

void CodeGenerator::visit(PrintStatement *printStmt) {
	if (printStmt == NULL) return;	
}

void CodeGenerator::visit(BreakStatement *breakStmt) {
	if (breakStmt == NULL) return;	
}

void CodeGenerator::visit(ContinueStatement *continueStmt) {
	if (continueStmt == NULL) return;
}

void CodeGenerator::visit(IncDecStatement *incDecStmt) {
	if (incDecStmt == NULL) return;	
}

void CodeGenerator::visit(ReturnStatement *returnStmt) {
	if (returnStmt == NULL) return;
}

void CodeGenerator::visit(EmptyStatement *emptyStmt) {
	if (emptyStmt == NULL) return;	
}

void CodeGenerator::visit(ArrayExp *arrExp) {
	if (arrExp == NULL) return;
}

void CodeGenerator::visit(BinaryOperatorExp *binOpExp) {
	if (binOpExp == NULL) return;
}

void CodeGenerator::visit(BoolExp *boolExp) {
	if (boolExp == NULL) return;
}

void CodeGenerator::visit(BuiltinsExp *builtinsExp) {
	if (builtinsExp == NULL) return;
}

void CodeGenerator::visit(FloatExp *floatExp) {
	if (floatExp == NULL) return;
}

void CodeGenerator::visit(FunctionCallExp *funcCallExp) {
	if (funcCallExp == NULL) return;
}

void CodeGenerator::visit(IdentifierExp *idExp) {
	if (idExp == NULL) return;
}

void CodeGenerator::visit(IntegerExp *intExp) {
	if (intExp == NULL) return;
}

void CodeGenerator::visit(RuneExp *runeExp) {
	if (runeExp == NULL) return;
}

void CodeGenerator::visit(StringExp *strExp) {
	if (strExp == NULL) return;
}

void CodeGenerator::visit(UnaryExp *unaryExp) {
	if (unaryExp == NULL) return;
}

#endif
