#ifndef CODE_GENERATOR_CPP
#define CODE_GENERATOR_CPP

#include <sstream>
#include <iostream>
#include <fstream>
#include "Services/CodeGenerator.hpp"
#include "AST/ASTTraversal.hpp"
#include "TypeDescriptorTable/TypeDescriptorTable.hpp"
#include "Const/Constants/Constants.hpp"

const std::string FILE_PATH = "./";
const std::string FILE_NAME = "__golite_target_code";
const std::string EXTENSION = ".c";

void CodeGenerator::emit(Program *prg, SymbolTable *st) {
	symbolTable = st;
	TypeDescriptorTable::getInstance().append(BASETYPE_INT, C_INT);
	TypeDescriptorTable::getInstance().append(BASETYPE_FLOAT, C_DOUBLE);
	TypeDescriptorTable::getInstance().append(BASETYPE_STRING, C_STRING);
	TypeDescriptorTable::getInstance().append(BASETYPE_RUNE, C_CHAR);
	TypeDescriptorTable::getInstance().append(BASETYPE_BOOL, C_BOOL);
	ASTTraversal::traverse(prg, *this);
}

//========================HELPER FUNCTIONS=========================
//=================================================================

void CodeGenerator::terminate() {
}

void CodeGenerator::saveToFile(
	const std::string &path,
	const std::string &name,
	const std::string &ext	// extension
) {
	std::stringstream ss;
	ss << path << name << ext;
	std::ofstream file;
	file.open(ss.str());
	file << outCode.str();
	file.close();
}

//=====================END OF HELPER FUNCTIONS=====================
//=================================================================


//=========================VISITOR PATTERN=========================
//=================================================================

void CodeGenerator::visit(Program *prg) {
	if (prg == NULL) return;
	
	if (isScopeOpened) {
		// initialization
		outCode << prg->preambleToCcode();
	} else {
		// generate main function	
		outCode << prg->mainToCcode(
					mainFuncCall.str(), 
					initFuncCalls.str()
		);
		std::cout << outCode.str() << std::endl;
		saveToFile(FILE_PATH, FILE_NAME, EXTENSION);
	} 
}

void CodeGenerator::visit(VariableDeclaration *varDecl) {
	if (varDecl == NULL) return;
}

void CodeGenerator::visit(TypeDeclaration *typeDecl) {
	if (typeDecl == NULL) return;
}

void CodeGenerator::visit(FunctionDeclaration *funcDecl) {
	if (funcDecl == NULL) return;

	outCode << funcDecl->toCcode(initFuncNum);

	if (funcDecl->idExp->name.compare(SPECIALFUNC_INIT) == 0) {
		initFuncCalls << funcDecl->initCallToCcode(initFuncNum);
		initFuncNum++;
	}

	if (funcDecl->idExp->name.compare(SPECIALFUNC_MAIN) == 0)
		mainFuncCall << funcDecl->mainCallToCCode();
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

std::string CodeGenerator::getTabs() {
	std::stringstream ss;
	for(int i = 0; i < numTabs; i++) {
		ss << "\t";
	}
	return ss.str();
}

#endif
