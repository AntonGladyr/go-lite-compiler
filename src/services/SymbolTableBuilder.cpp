#ifndef SYMBOLTABLEBUILDER_CPP
#define SYMBOLTABLEBUILDER_CPP

#include <iostream>
#include "Services/SymbolTableBuilder.hpp"
#include "SymbolTable/SymbolTable.hpp"
#include "SymbolTable/Symbol.hpp"
#include "AST/ASTTraversal.hpp"

// initializes a symbol table
SymbolTable *SymbolTableBuilder::build(Program *prg) {
	//copy program pointer for deallocation
	program = prg;
	
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


//=====================HELPER FUNCTIONS===========================
//=================================================================


// termination after errors
void SymbolTableBuilder::terminate() {
	symbolTable->deallocate();
	delete symbolTable;
	symbolTable = NULL;
	delete program;
	program = NULL;	
	exit(1);
}

// helper function for inserting function parameters into scope
void SymbolTableBuilder::insertFuncParams(Node *node) {	
	if (typeid(FunctionDeclaration) == typeid(*node)) {	
		FunctionDeclaration *funcDecl = (FunctionDeclaration*)node;
		std::stringstream paramType;

		if (funcDecl->params) {
			for (auto const& param : *(funcDecl->params)) {
				//clear string stream
				paramType.str(std::string());
				
				// array indexes
                       		if (param->second->second) {
					for(auto const& index : *(param->second->second)) {
						paramType << "[" << std::to_string(index) << "]";
					}
				}
                          	// type
				paramType << param->second->first;
				
				//save pointer to the parent node in idExp
				funcDecl->idExp->parentNode = funcDecl;	
				Symbol *symbol = symbolTable->putSymbol(
					param->first->id,
					CATEGORY_VAR,
					paramType.str(),
					funcDecl->idExp 
				);
	
				// terminate if id already declared
				if (symbol == NULL) terminate();
				
				// pass to stream for printing
				ss << getTabs() << param->first->id << " [" << CATEGORY_VAR << "]"
				   << " = " << paramType.str() << std::endl;
			}
		}
	}
}

// check init and main functions
void SymbolTableBuilder::checkSpecialFunctions(Node *node) {
	//TODO: change default type of init func to <unmapped>
	if (typeid(FunctionDeclaration) == typeid(*node)) {
		FunctionDeclaration *funcDecl = (FunctionDeclaration*)node;
		
		// return if not "main" nor "init"
		if ((funcDecl->idExp->id.compare(SPECIALFUNC_MAIN) != 0) &&
			(funcDecl->idExp->id.compare(SPECIALFUNC_INIT) != 0)) return;

		if(funcDecl->type || funcDecl->params) {
			std::cerr << ss.str();
			std::cerr << "Error: (line " << funcDecl->idExp->lineno << ") " << funcDecl->idExp->id 
				  << " must have no parameters and no return value" << std::endl;
			terminate();
		}
	}
}

// check if type is declared
void SymbolTableBuilder::resolveType(const std::string &type, int lineno) {
	Symbol *s = symbolTable->getSymbol(symbolTable, type);
	
	// check if identifier exists in the symbol table
	if (s == NULL) {
		std::cerr << ss.str();
		std::cerr << "Error: (line " << lineno << ") type \"" << type << "\" is not declared" << std::endl;	
		terminate();
	}

	// check if identifier has "type" category
	if (s->category.compare(CATEGORY_TYPE) != 0) {
		std::cerr << ss.str();
		std::cerr << "Error: (line " << lineno << ") \"" << type << "\" is not a type" << std::endl;
		terminate();
	}
}

// check identifier name ('main' and 'init' must be a function)
void SymbolTableBuilder::checkIdName(Node *node) {	
	if (typeid(IdentifierExp) != typeid(*node)) return;
	
	IdentifierExp * idExp = (IdentifierExp*)node;	
	if (idExp->id.compare(SPECIALFUNC_MAIN) == 0 ||
	    idExp->id.compare(SPECIALFUNC_INIT) == 0) 
	{
		std::cerr << ss.str();
		std::cerr << "Error: (line " << idExp->lineno << ") "
			  << idExp->id << " must be a function" << std::endl;
		 terminate();
	}
}

// check if the number of ids is equal to the number of expressions
void SymbolTableBuilder::checkAssignEquality(
	int lhsSize,
	int rhsSize,
	Node *node
) {
	if (rhsSize == 0) return;
	
	if (lhsSize != rhsSize) {
		std::cerr << ss.str();
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

//=====================END OF HELPER FUNCTIONS=====================
//=================================================================


//=====================VISITOR PATTERN=============================
//=================================================================

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
		
	//copy string stream for printing errors
	symbolTable->ss.str(ss.str());
	
	// check if expression identifiers exist in the symbol table
	if (varDecl->expList) {
		for(auto const& exp : *(varDecl->expList)) {
			ASTTraversal::traverse(exp, *this);
		}
	}
	
	//check if number of ids equals to the number of the expressions
	if (varDecl->expList)
		checkAssignEquality(varDecl->idList->size(), varDecl->expList->size(), varDecl);
		
	// reverse iteration for identifiers
	for (auto var = varDecl->idList->rbegin(); var != varDecl->idList->rend(); var++) {
		std::stringstream type;
		
		// check if a variable name is not 'main' nor 'init'
		// parent->parent => basetypes
		if (symbolTable->parent->parent == NULL) checkIdName(*var);	
		
		if (varDecl->type) {
			//check if type exists
			resolveType(varDecl->type->first, (*var)->lineno);
			
			if (varDecl->type->second) {
				for(auto const& index : *(varDecl->type->second)) {
					type << "[" << std::to_string(index) << "]";
				}
			}
			
			type << varDecl->type->first;
		} else {
			type << BASETYPE_UNDEFINED;
		}
		
		ss << getTabs() << (*var)->id << " [" << CATEGORY_VAR << "]" << " = ";
		ss << type.str() << std::endl;
		
		//save pointer to the parent node in idExp
		(*var)->parentNode = varDecl;	
		Symbol *symbol = symbolTable->putSymbol(
			(*var)->id,
			CATEGORY_VAR,
			type.str(),
			*var
		);
		
		// terminate if id already declared
		if (symbol == NULL) terminate();
		
		// save to the node
		(*var)->symbol = symbol;
	}
}

void SymbolTableBuilder::visit(TypeDeclaration *typeDecl) {
	if (typeDecl == NULL) return;

	//copy string stream for printing errors
	symbolTable->ss.str(ss.str());
	
	// check if type name is not 'main' nor 'init'
	//parent->parent => basetypes
	if (symbolTable->parent->parent == NULL) checkIdName(typeDecl->idExp);

	//check if type exists
	if (typeDecl->type)
		resolveType(typeDecl->type->first, typeDecl->idExp->lineno);
	
	//check for recursive type declarations
	if(typeDecl->idExp->id.compare(typeDecl->symbolTypeToStr()) == 0) {
		std::cerr << ss.str();
		std::cerr << "Error: (line " << typeDecl->idExp->lineno
			  << ") invalid recursive type " << typeDecl->symbolTypeToStr() << std::endl;
		terminate();
	}
	
	//save pointer to the parent node in idExp
	typeDecl->idExp->parentNode = typeDecl;
	Symbol *symbol = symbolTable->putSymbol(
		typeDecl->idExp->id,
		CATEGORY_TYPE,
		typeDecl->symbolTypeToStr(),
		typeDecl->idExp
	);
	
	// terminate if id already declared
	if (symbol == NULL) terminate();

	typeDecl->symbol = symbol;
	ss << getTabs() << typeDecl->symbolToStr() << std::endl;
}

void SymbolTableBuilder::visit(FunctionDeclaration *funcDecl) {
	if (funcDecl == NULL) return;

	// copy string stream for printing errors
	symbolTable->ss.str(ss.str());

	// check special functions: init and main
	checkSpecialFunctions(funcDecl);
	
	// check if return type exists
	if (funcDecl->type)
		resolveType(funcDecl->type->first, funcDecl->idExp->lineno);

	// check if parameter types exist
	if (funcDecl->params) {
		for (auto const& param : *(funcDecl->params)) {
			resolveType(param->second->first, funcDecl->idExp->lineno);
		}
	}
	
	// save pointer to the parent node (func declaration) in the block statement,
	// so func parameters can be added to the child scope
	funcDecl->blockStmt->parentNode = funcDecl;
	funcDecl->idExp->parentNode = funcDecl;
	Symbol *symbol = symbolTable->putSymbol(
		funcDecl->idExp->id,
		CATEGORY_FUNC,
		funcDecl->symbolTypeToStr(),
		funcDecl->idExp
	);
	
	// terminate if id already declared
	if (symbol == NULL) terminate();

	funcDecl->symbol = symbol;
	ss << getTabs() << funcDecl->symbolToStr() << std::endl;
}

void SymbolTableBuilder::visit(BlockStatement *blockStmt) {
	if (blockStmt == NULL) return;
		
	if (isScopeOpened) {
		// open new scope
		symbolTable = symbolTable->scopeSymbolTable();
		
		ss << getTabs() << "{" << std::endl;
		numTabs++;
		
		// if parent node is FuncDecl, put func parameters to the symbol table
		if (blockStmt->parentNode) {
			if (typeid(FunctionDeclaration) == typeid(*(blockStmt->parentNode)))
				insertFuncParams(blockStmt->parentNode);
		}
		
	} else {
		// close scope
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

void SymbolTableBuilder::visit(AssignStatement *assignStmt) {
	if (assignStmt == NULL) return;
	
	checkAssignEquality(assignStmt->lhs->size(), assignStmt->rhs->size(), assignStmt);
}

void SymbolTableBuilder::visit(ExpressionStatement *expStmt) {
	if (expStmt == NULL) return;
	
	// if a given expression is not a function call, throw an error
	if(dynamic_cast<FunctionCallExp*>(expStmt->exp) == nullptr) {
		std::cerr << ss.str();
		std::cerr << "Error: (line " << expStmt->exp->lineno << ") "
			  << "expression statements must be function calls" << std::endl;
		terminate();
	}
	
	ASTTraversal::traverse(expStmt->exp, *this);
}

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

void SymbolTableBuilder::visit(ArrayExp *arrExp) {
	if (arrExp == NULL) return;
}

void SymbolTableBuilder::visit(BinaryOperatorExp *binOpExp) {
	if (binOpExp == NULL) return;
}

void SymbolTableBuilder::visit(BoolExp *boolExp) {
	if (boolExp == NULL) return;
}

void SymbolTableBuilder::visit(BuiltinsExp *builtinsExp) {
	if (builtinsExp == NULL) return;
}

void SymbolTableBuilder::visit(FloatExp *floatExp) {
	if (floatExp == NULL) return;
}

void SymbolTableBuilder::visit(FunctionCallExp *funcCallExp) {
	if (funcCallExp == NULL) return;
		
	// copy string stream for printing errors
	symbolTable->ss.str(ss.str());
	
	ASTTraversal::traverse(funcCallExp->idExp, *this);
	
	// check if parameter identifiers exist in the symbol table
	if (funcCallExp->expList) {
		for(auto const& exp : *funcCallExp->expList) {
			ASTTraversal::traverse(exp, *this);
		}
	}
}

void SymbolTableBuilder::visit(IdentifierExp *idExp) {
	if (idExp == NULL) return;
		
	// check if function identifier exists
	if(symbolTable->getSymbol(symbolTable, idExp->id) == NULL) {
		std::cerr << ss.str();
		std::cerr << "Error: (line " << idExp->lineno << ") \""
		  << idExp->id << "\" is not declared" << std::endl;
		terminate();
	}
}

void SymbolTableBuilder::visit(IntegerExp *intExp) {
	if (intExp == NULL) return;
}

void SymbolTableBuilder::visit(RuneExp *runeExp) {
	if (runeExp == NULL) return;
}

void SymbolTableBuilder::visit(StringExp *strExp) {
	if (strExp == NULL) return;
}

void SymbolTableBuilder::visit(UnaryExp *unaryExp) {
	if (unaryExp == NULL) return;
}



std::string SymbolTableBuilder::getTabs() {
	std::stringstream ss;
	for(int i = 0; i < numTabs; i++) {
		ss << "\t";
	}
	return ss.str();
}

#endif
