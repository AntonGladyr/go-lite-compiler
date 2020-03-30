#ifndef PRETTYPRINTER_CPP
#define PRETTYPRINTER_CPP

#include <sstream>
#include <iostream>
#include "Services/PrettyPrinter.hpp"
#include "AST/ASTTraversal.hpp"
#include "../helpers/vectorExtension.cpp"

void PrettyPrinter::visit(Program *prg) {
	if (prg == NULL) return;
	std::cout << prg->toString() << std::endl;
}

void PrettyPrinter::visit(VariableDeclaration *varDecl) {
	if (varDecl == NULL) return;
	std::cout << getTabs() << varDecl->toString() << std::endl;
}

void PrettyPrinter::visit(TypeDeclaration *typeDecl) {
	if (typeDecl == NULL) return;	
	std::cout << getTabs() << typeDecl->toString() << std::endl;
}

void PrettyPrinter::visit(FunctionDeclaration *funcDecl) {
	if (funcDecl == NULL) return;
	std::cout << getTabs() << funcDecl->toString();
}

void PrettyPrinter::visit(BlockStatement *blockStmt) {
	if (blockStmt == NULL) return;
	
	if (isScopeOpened) {
		std::cout << "{" << std::endl;
		numTabs++;
	} else {
		numTabs--;
		std::cout << getTabs() << "}" << std::endl;
	}
}

void PrettyPrinter::visit(DeclarationStatement *declStmt) {	
	if (declStmt == NULL) return;
	std::cout << getTabs() << declStmt->toString() << std::endl;
}

void PrettyPrinter::visit(TypeDeclarationStatement *typeDeclStmt) {
	if (typeDeclStmt == NULL) return;
	std::cout << getTabs() << typeDeclStmt->toString() << std::endl;
}

void PrettyPrinter::visit(AssignStatement *assignStmt) {
	if (assignStmt == NULL) return;
	std::cout << getTabs() << assignStmt->toString() << std::endl;
}

void PrettyPrinter::visit(ExpressionStatement *expStmt) {
	if (expStmt == NULL) return;
	std::cout << getTabs() << expStmt->toString() << std::endl;
}

void PrettyPrinter::visit(ForStatement *forStmt) {
	if (forStmt == NULL) return;
	std::cout << getTabs() << forStmt->toString();
}

void PrettyPrinter::visit(IfElseStatement *ifElseStmt) {	
	if (ifElseStmt == NULL) return;
	
	std::cout << getTabs() << "if " << ifElseStmt->exp->toString() << " ";
	ASTTraversal::traverse(ifElseStmt->blockStmt, *this);
	
	if (ifElseStmt->ifStmt) {
		std::cout << getTabs() << "else ";
		ASTTraversal::traverse(ifElseStmt->ifStmt, *this);
	}
	
	if (ifElseStmt->elseBlockStmt ) {
		std::cout << getTabs() << "else ";
		ASTTraversal::traverse(ifElseStmt->elseBlockStmt, *this);
	}
}

void PrettyPrinter::visit(IfStatement *ifStmt) {
	if (ifStmt == NULL) return;
	std::cout << getTabs() << ifStmt->toString();
}

void PrettyPrinter::visit(SwitchStatement *switchStmt) {
	if (switchStmt == NULL) return;
	
	std::cout << getTabs() << "switch";
	if (switchStmt->exp) std::cout << " " << switchStmt->exp->toString();
	std::cout << " {" << std::endl;
	numTabs++;
	if (switchStmt->clauseList) {	
		for(auto const& clause : *(switchStmt->clauseList)) {
			if (clause->second == SWITCH_CLAUSE::CASE) {
				std::cout << getTabs() << "case";
			}

			if (clause->second == SWITCH_CLAUSE::DEFAULT) {	
				std::cout << getTabs() << "default";
			}
			
			if (clause->first) {
				if (clause->first->first) {
					std::cout << " " << *(clause->first->first);
				}

				std::cout << ":";

				if (clause->first->second) {
					ASTTraversal::traverse(clause->first->second, *this);
				}
			}
		}
	}
	
	numTabs--;
	std::cout << getTabs() << "}" << std::endl;
}

void PrettyPrinter::visit(PrintStatement *printStmt) {
	if (printStmt == NULL) return;
	std::cout << getTabs() << printStmt->toString() << std::endl;
}

void PrettyPrinter::visit(BreakStatement *breakStmt) {
	if (breakStmt == NULL) return;
	std::cout << getTabs() << breakStmt->toString() << std::endl;
}

void PrettyPrinter::visit(ContinueStatement *continueStmt) {
	if (continueStmt == NULL) return;
	std::cout << getTabs() << continueStmt->toString() << std::endl;
}

void PrettyPrinter::visit(IncDecStatement *incDecStmt) {
	if (incDecStmt == NULL) return;
	std::cout << getTabs() << incDecStmt->toString() << std::endl;
}

void PrettyPrinter::visit(ReturnStatement *returnStmt) {
	if (returnStmt == NULL) return;
	std::cout << getTabs() << returnStmt->toString() << std::endl;
}

void PrettyPrinter::visit(EmptyStatement *emptyStmt) {
	if (emptyStmt == NULL) return;
	//std::cout << getTabs() << emptyStmt->toString() << std::endl;
}

std::string PrettyPrinter::getTabs() {
	std::stringstream ss;
	for(int i = 0; i < numTabs; i++) {
		ss << "\t";
	}
	return ss.str();
}

#endif
