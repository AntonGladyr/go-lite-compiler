#ifndef SYMBOLTABLEBUILDER_CPP
#define SYMBOLTABLEBUILDER_CPP

#include <iostream>
#include "Services/SymbolTableBuilder.hpp"
#include "SymbolTable/SymbolTable.hpp"
#include "SymbolTable/Symbol.hpp"
#include "AST/ASTTraversal.hpp"

SymbolTable *SymbolTableBuilder::build(Program *prg) {
	ss << "{" << std::endl;
	numTabs++;
	symbolTable = new SymbolTable();
	Symbol *symb = NULL;
	
	// pre-declared mappings
	symb = symbolTable->putSymbol(BASETYPE_INT, CATEGORY_TYPE, BASETYPE_INT, NULL);
	ss << getTabs() << BASETYPE_INT << " [" << CATEGORY_TYPE << "]" << " = " << BASETYPE_INT << std::endl;
	symb = symbolTable->putSymbol(BASETYPE_FLOAT, CATEGORY_TYPE, BASETYPE_FLOAT, NULL);
	ss << getTabs() << BASETYPE_FLOAT << " [" << CATEGORY_TYPE << "]" << " = " << BASETYPE_FLOAT << std::endl;	
	symb = symbolTable->putSymbol(BASETYPE_RUNE, CATEGORY_TYPE, BASETYPE_RUNE, NULL);
	ss << getTabs() << BASETYPE_RUNE << " [" << CATEGORY_TYPE << "]" << " = " << BASETYPE_RUNE << std::endl;
	symb = symbolTable->putSymbol(BASETYPE_STRING, CATEGORY_TYPE, BASETYPE_STRING, NULL);
	ss << getTabs() << BASETYPE_STRING << " [" << CATEGORY_TYPE << "]" << " = " << BASETYPE_STRING << std::endl;
	symb = symbolTable->putSymbol(BASETYPE_BOOL, CATEGORY_TYPE, BASETYPE_BOOL, NULL);
	ss << getTabs() << BASETYPE_BOOL << " [" << CATEGORY_TYPE << "]" << " = " << BASETYPE_BOOL << std::endl;
	symb = symbolTable->putSymbol(CONSTANT_TRUE, CATEGORY_CONST, BASETYPE_BOOL, NULL);
	ss << getTabs() << CONSTANT_TRUE << " [" << CATEGORY_CONST << "]" << " = " << BASETYPE_BOOL << std::endl;
	symb = symbolTable->putSymbol(CONSTANT_FALSE, CATEGORY_CONST, BASETYPE_BOOL, NULL);
	ss << getTabs() << CONSTANT_FALSE << " [" << CATEGORY_CONST << "]" << " = " << BASETYPE_BOOL << std::endl;
	
	//traverse the AST
	ASTTraversal::traverse(prg, *this);
	
	numTabs--;
	ss << "}" << std::endl;	
	symbolTable->ss << ss.str();
	return symbolTable;
}

void SymbolTableBuilder::resolveType(SymbolTable *symbolTable, const std::string &type, int lineno) {
	if (symbolTable->getSymbol(symbolTable, type)) return;
	std::cerr << ss.str();
	std::cerr << "Error: (line " << lineno << ") type \"" << type << "\" is not declared" << std::endl;
	exit(1);		
}

void SymbolTableBuilder::visit(Program *prg) {
	if (prg == NULL) return;
	
	if (isScopeOpened) {
		symbolTable = symbolTable->scopeSymbolTable();
		ss << getTabs() << "{" << std::endl;	
		numTabs++;	
	} else {
		symbolTable = symbolTable->unscopeSymbolTable();
		numTabs--;
		ss << getTabs() << "}" << std::endl;
	}
}

void SymbolTableBuilder::visit(VariableDeclaration *varDecl) {
	if (varDecl == NULL) return;
	
	// reverse iteration
	for (auto var = varDecl->idList->rbegin(); var != varDecl->idList->rend(); var++) {
		std::stringstream type;
		ss << getTabs() << (*var)->value << " [" << CATEGORY_VAR << "]" << " = ";	
		
		if (varDecl->type) {
			//check if type exists
			resolveType(symbolTable, varDecl->type->first, varDecl->lineno);
			
			if (varDecl->type->second) {
				for(auto const& index : *(varDecl->type->second)) {
					type << "[" << std::to_string(index) << "]";
				}
			}
			
			type << varDecl->type->first;
		} else {
			type << BASETYPE_UNDEFINED;
		}
		
		ss << type.str() << std::endl;

		Symbol *symbol = symbolTable->putSymbol(
			(*var)->value,
			CATEGORY_VAR,
			type.str(),
			varDecl
		);
		(*var)->symbol = symbol;
	}
}

void SymbolTableBuilder::visit(TypeDeclaration *typeDecl) {
	if (typeDecl == NULL) return;
	
	//check if type exists
	if (typeDecl->type)
		resolveType(symbolTable, typeDecl->type->first, typeDecl->lineno);
	
	Symbol *symbol = symbolTable->putSymbol(
		typeDecl->id,
		CATEGORY_TYPE,
		typeDecl->symbolTypeToStr(),
		typeDecl
	);
	typeDecl->symbol = symbol;
	ss << getTabs() << typeDecl->symbolToStr() << std::endl;
}

void SymbolTableBuilder::visit(FunctionDeclaration *funcDecl) {
	if (funcDecl == NULL) return;
	
	//check if return type exists
	if (funcDecl->type)
		resolveType(symbolTable, funcDecl->type->first, funcDecl->lineno);
	//check if parameter types exist
	if (funcDecl->params) {
		for (auto const& param : *(funcDecl->params)) {
			resolveType(symbolTable, param->second->first, funcDecl->lineno);
		}
	}
	
	Symbol *symbol = symbolTable->putSymbol(
		funcDecl->id,
		CATEGORY_FUNC,
		funcDecl->symbolSignatureToStr(),
		funcDecl);
	funcDecl->symbol = symbol;
	ss << getTabs() << funcDecl->symbolToStr() << std::endl;
}

void SymbolTableBuilder::visit(BlockStatement *blockStmt) {
	if (blockStmt == NULL) return;
	
	if (isScopeOpened) {
		symbolTable = symbolTable->scopeSymbolTable();
		ss << getTabs() << "{" << std::endl;
		numTabs++;
	} else {
		symbolTable = symbolTable->unscopeSymbolTable();
		numTabs--;
		ss << getTabs() << "}" << std::endl;
	}
}

void SymbolTableBuilder::visit(DeclarationStatement *declStmt) {	
	if (declStmt == NULL) return;
	ASTTraversal::traverse(declStmt->decl, *this);
}

void SymbolTableBuilder::visit(TypeDeclarationStatement *typeDeclStmt) {
	if (typeDeclStmt == NULL) return;
	ASTTraversal::traverse(typeDeclStmt->typeDecl, *this);
}

void SymbolTableBuilder::visit(AssignStatement *assignStmt) { }

void SymbolTableBuilder::visit(ExpressionStatement *expStmt) { }

void SymbolTableBuilder::visit(ForStatement *forStmt) { }

void SymbolTableBuilder::visit(IfElseStatement *ifElseStmt) {	
	if (ifElseStmt == NULL) return;
	
	ASTTraversal::traverse(ifElseStmt->blockStmt, *this);
	
	if (ifElseStmt->ifStmt) {	
		ASTTraversal::traverse(ifElseStmt->ifStmt, *this);
	}
	
	if (ifElseStmt->elseBlockStmt ) {	
		ASTTraversal::traverse(ifElseStmt->elseBlockStmt, *this);
	}
}

void SymbolTableBuilder::visit(IfStatement *ifStmt) { }

void SymbolTableBuilder::visit(SwitchStatement *switchStmt) {
	if (switchStmt == NULL) return;
	
	symbolTable = symbolTable->scopeSymbolTable();
	ss << getTabs() << "{" << std::endl;	
	numTabs++;	
	
	if (switchStmt->clauseList) {	
		for(auto const& clause : *(switchStmt->clauseList)) {	
			if (clause->first) {
				if (clause->first->second) {
					ASTTraversal::traverse(clause->first->second, *this);
				}
			}
		}
	}

	symbolTable = symbolTable->unscopeSymbolTable();
	numTabs--;
	ss << getTabs() << "}" << std::endl;
}

void SymbolTableBuilder::visit(PrintStatement *printStmt) { }

void SymbolTableBuilder::visit(BreakStatement *breakStmt) { }

void SymbolTableBuilder::visit(ContinueStatement *continueStmt) { }

void SymbolTableBuilder::visit(IncDecStatement *incDecStmt) { }

void SymbolTableBuilder::visit(ReturnStatement *returnStmt) { }

void SymbolTableBuilder::visit(EmptyStatement *emptyStmt) { }

std::string SymbolTableBuilder::getTabs() {
	std::stringstream ss;
	for(int i = 0; i < numTabs; i++) {
		ss << "\t";
	}
	return ss.str();
}

#endif
