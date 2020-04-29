#ifndef WEEDER_CPP
#define WEEDER_CPP

#include <sstream>
#include <iostream>
#include "Services/Weeder.hpp"
#include "AST/ASTTraversal.hpp"

// check if the number of ids is equal to the number of expressions
void Weeder::checkAssignEquality(
	int lhsSize,
	int rhsSize,
	Node *node
) {
	if (rhsSize == 0) return;

	if (lhsSize != rhsSize) {
		std::cerr << "Error: (line " << node->lineno << ") ";
		if (typeid(VariableDeclaration) == typeid(*node))
			std::cerr << "variable declaration ";
		if (typeid(AssignStatement) == typeid(*node))
			std::cerr << "assignment ";
		std::cerr << "lhs(" << lhsSize << ")"
			<< " != rhs(" << rhsSize << ")" << std::endl;
		terminate();
	}	
}


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

	//check if number of ids equals to the number of the expressions
	if (varDecl->expList)
		checkAssignEquality(varDecl->idList->size(), varDecl->expList->size(), varDecl);
}

void Weeder::visit(TypeDeclaration *typeDecl) {
	if (typeDecl == NULL) return;		
}

void Weeder::visit(FunctionDeclaration *funcDecl) {
	if (funcDecl == NULL) return;

	funcDecl->blockStmt->parentNode = funcDecl;
}

void Weeder::visit(BlockStatement *blockStmt) {
	if (blockStmt == NULL) return;
	
	if (isScopeOpened) {
		// save pointer to the base (function) block in each statement
		if (blockStmt->stmtList) {
			for(auto &stmt : *(blockStmt->stmtList)) {	
				// save pointer to the parent node in each statement
				stmt->parentNode = blockStmt->parentNode;
			}
		}
	}
}

void Weeder::visit(DeclarationStatement *declStmt) {
	if (declStmt == NULL) return;
}

void Weeder::visit(TypeDeclarationStatement *typeDeclStmt) {
	if (typeDeclStmt == NULL) return;
}

void Weeder::visit(AssignStatement *assignStmt) {
	if (assignStmt == NULL) return;

	checkAssignEquality(assignStmt->lhs->size(), assignStmt->rhs->size(), assignStmt);
}

void Weeder::visit(ExpressionStatement *expStmt) {
	if (expStmt == NULL) return;

	// if a given expression is not a function call, throw an error
	if (typeid(FunctionCallExp) != typeid(*(expStmt->exp))) {
		std::cerr << "Error: (line " << expStmt->exp->lineno << ") "
			  << "expression statement must be a function call" << std::endl;
		terminate();
	}
}

void Weeder::visit(ForStatement *forStmt) {
	if (forStmt == NULL) return;
	
	forStmt->blockStmt->parentNode = forStmt;
	
	// check init stmt
	if (forStmt->initStmt)
		ASTTraversal::traverse(forStmt->initStmt, *this);

	// check loop post statement
	if (forStmt->postStmt)
		ASTTraversal::traverse(forStmt->postStmt, *this);
}

void Weeder::visit(IfElseStatement *ifElseStmt) {	
	if (ifElseStmt == NULL) return;
	
	ifElseStmt->blockStmt->parentNode = ifElseStmt;
	
	ASTTraversal::traverse(ifElseStmt->blockStmt, *this);
	
	if (ifElseStmt->ifStmt) {	
		ASTTraversal::traverse(ifElseStmt->ifStmt, *this);
	}
	
	if (ifElseStmt->elseBlockStmt) {
		ifElseStmt->elseBlockStmt->parentNode = ifElseStmt;
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
				clause->blockStmt->parentNode = switchStmt;
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
	
	Statement *stmt = NULL;	
	
	if ( continueStmt->parentNode &&
	     typeid(ForStatement) == typeid(*(continueStmt->parentNode))
	) {
		return;
	}
	
	std::cerr << "Error: (line " << continueStmt->lineno << ") "
		  << "continue must occur within a loop context" << std::endl;
	terminate();
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
