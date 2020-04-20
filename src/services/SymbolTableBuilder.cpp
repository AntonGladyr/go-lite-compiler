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
	std::exit(EXIT_FAILURE);
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
				
				if (param->typeName == NULL) terminate();

				// array indexes
                       		if (param->typeName->indexes) {
					for(auto const& index : *(param->typeName->indexes)) {
						paramType << "[" << std::to_string(index) << "]";
					}
				}
                          	// type
				paramType << param->typeName->name;
				
				//save pointer to the parent node in idExp
				funcDecl->idExp->parentNode = funcDecl;	
				Symbol *symbol = symbolTable->putSymbol(
					param->idExp->name,
					CATEGORY_VAR,
					paramType.str(),
					funcDecl->idExp 
				);
	
				// terminate if id already declared
				if (symbol == NULL) terminate();
				
				// pass to stream for printing
				ss << getTabs() << param->idExp->name << " [" << CATEGORY_VAR << "]"
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
		if ((funcDecl->idExp->name.compare(SPECIALFUNC_MAIN) != 0) &&
			(funcDecl->idExp->name.compare(SPECIALFUNC_INIT) != 0)) return;

		if(funcDecl->typeName || funcDecl->params) {
			std::cerr << ss.str();
			std::cerr << "Error: (line " << funcDecl->idExp->lineno << ") " << funcDecl->idExp->name 
				  << " must have no parameters and no return value" << std::endl;
			terminate();
		}
	}
}

// check if type is declared
void SymbolTableBuilder::checkTypeName(TypeName *type) {
	Symbol *s = symbolTable->getSymbol(symbolTable, type->name);
	
	// check if identifier exists in the symbol table
	if (s == NULL) {
		std::cerr << ss.str();
		std::cerr << "Error: (line " << type->lineno << ") type \""
			  << type->name << "\" is not declared" << std::endl;	
		terminate();
	}

	// check if identifier has "type" category
	if (s->category.compare(CATEGORY_TYPE) != 0) {
		std::cerr << ss.str();
		std::cerr << "Error: (line " << type->lineno << ") \""
			  << type->name << "\" is not a type" << std::endl;
		terminate();
	}
}

// check identifier name ('main' and 'init' must be a function)
void SymbolTableBuilder::checkIdName(Node *node) {	
	if (typeid(IdentifierExp) != typeid(*node)) return;
	
	IdentifierExp *idExp = (IdentifierExp*)node;
	if (idExp->name.compare(SPECIALFUNC_MAIN) == 0 ||
	    idExp->name.compare(SPECIALFUNC_INIT) == 0) 
	{
		std::cerr << ss.str();
		std::cerr << "Error: (line " << idExp->lineno << ") "
			  << idExp->name << " must be a function" << std::endl;
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

// throws an error if call of an init function occurs
void SymbolTableBuilder::checkIsInitFunc(FunctionCallExp *funcCallExp) {
	if (funcCallExp->idExp->name.compare(SPECIALFUNC_INIT) == 0) {
		std::cerr << "Error: (line " << funcCallExp->lineno << ") "
			  << "init function may not be called" << std::endl;
		terminate();
	}
}

// throws an error if number of passed parameters to a function does not equal to the number of function arguments
void SymbolTableBuilder::checkNumberOfFuncArgs(FunctionCallExp *funcCallExp) {
	FunctionDeclaration *funcDecl = (FunctionDeclaration*)funcCallExp->idExp->symbol->node;
	
	if (funcCallExp->expList->size() != funcDecl->params->size()) {
		std::cerr << "Error: (line " << funcCallExp->lineno << ") "
			  << "function " << funcCallExp->idExp->name
			  << " called with incorrect number of arguments [received "
			  << funcCallExp->expList->size() << ", expected "
			  << funcDecl->params->size() << "]" << std::endl;
		terminate();
	}
}

// throws an error if function call parameter has different type than in corresponding function declaration
void SymbolTableBuilder::checkArgTypes(FunctionCallExp *funcCallExp) {
	FunctionDeclaration *funcDecl = (FunctionDeclaration*)funcCallExp->idExp->symbol->node;
	
	int paramsNum = funcCallExp->expList->size();

	std::vector<FunctionParameter*>::iterator paramIter = funcDecl->params->begin();
	std::vector<Expression*>::iterator expIter = funcCallExp->expList->begin();

	while (paramIter != funcDecl->params->end() && expIter != funcCallExp->expList->end()) {
		if ((*expIter)->type.name.compare((*paramIter)->typeName->name) != 0) {
			std::cerr << "Error: (line " << funcCallExp->lineno << ") "
				  << (*expIter)->type.name
				  << " is not assignment compatible with "
				  << (*paramIter)->typeName->name << " in function call" << std::endl;
			terminate();
		}
		paramIter++;
		expIter++;
	}
}

// throws an error for malformed binary expressions
void SymbolTableBuilder::binaryExpError(
	const std::string &lhsType,
	const std::string &rhsType,	
	int lineno
) {
	// TODO: write more informative errors for different binary operators
	std::cerr << "Error: (line " << lineno << ") "
		  << "binary expression lhs type is incompatible with rhs type "
		  << "[" << lhsType << " != " << rhsType << "]" << std::endl; 
	terminate();
}

// throws an error if the given expression is not an array
void SymbolTableBuilder::checkIsArray(ArrayExp *arrExp) {
	IdentifierExp *idExp = NULL;
	VariableDeclaration *varDecl;
	
	Symbol *s = symbolTable->getSymbol(symbolTable, arrExp->idExp->name);	

	if (typeid(IdentifierExp) != typeid(*(s->node))) {
		std::cerr << "Error: (line " << arrExp->lineno << ") "
			  << "indexing target expects list target (slice, array) "
			  << "[received " << getReceivedTypeName(arrExp->idExp)
			  << "]" << std::endl;
		terminate();
	}
	
	idExp = (IdentifierExp*)s->node;
	
	if (typeid(VariableDeclaration) != typeid(*(idExp->parentNode))) {
		std::cerr << "Error: (line " << arrExp->lineno << ") "
			  << "indexing target expects list target (slice, array) "
			  << "[received " << getReceivedTypeName(arrExp->idExp)
			  << "]" << std::endl;
		terminate();
	}
	
	varDecl = (VariableDeclaration*)idExp->parentNode;

	if (varDecl->typeName->indexes == NULL) {
		std::cerr << "Error: (line " << arrExp->lineno << ") "
			  << "indexing target expects list target (slice, array) "
			  << "[received " << getReceivedTypeName(arrExp->idExp)
			  << "]" << std::endl;
		terminate();
	}
}

void SymbolTableBuilder::checkIsIntExp(Expression *exp) {	
	if (exp->type.baseType.compare(BASETYPE_INT) != 0) {
		std::cerr << "Error: (line " << exp->lineno << ") "
			  << "index must be an int "
			  << "[received " << exp->type.name << "]" << std::endl;
		terminate();
	}
}

// return type name of an expression
std::string SymbolTableBuilder::getReceivedTypeName(Expression *exp) {
	std::stringstream receivedType;
	bool isTypeName = hasTypeName(exp);
	
	if (typeid(IdentifierExp) == typeid(*exp) && isTypeName) {
		IdentifierExp * idExp = (IdentifierExp*)exp;
		receivedType << "{" << idExp->name << "}";
	}
	else receivedType << exp->type.name;

	return receivedType.str();
}

// check if an identifier has the same name as a type
bool SymbolTableBuilder::hasTypeName(Expression *exp) {
	if (typeid(IdentifierExp) != typeid(*exp)) return false;
	
	IdentifierExp * idExp = (IdentifierExp*)exp;
	Symbol *s = symbolTable->getSymbol(symbolTable, idExp->name);
	return s->category.compare(CATEGORY_TYPE) == 0;
}

// prints an error for incompatible types
void SymbolTableBuilder::typeCompatibilityError(
	int lineno,
	const std::string &expName,
	const std::string &receivedType,
	const std::string &expectedType
) {
	std::cerr << "Error: (line " << lineno << ") incompatible type in " << expName
		  << " [received " << receivedType << ", expected " << expectedType << "]" << std::endl;
	terminate();
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
		// (parent->parent scope => basetypes)
		if (symbolTable->parent->parent == NULL) checkIdName(*var);
			
		//check type name
		if (varDecl->typeName) {
			//check if type exists
			checkTypeName(varDecl->typeName);
			if (varDecl->typeName->indexes) {	
				for(auto const& index : *(varDecl->typeName->indexes)) {
					type << "[" << std::to_string(index) << "]";
				}	
			}
			
			type << varDecl->typeName->name;
		} else {
			type << BASETYPE_UNDEFINED;
		}
		
		ss << getTabs() << (*var)->name << " [" << CATEGORY_VAR << "]" << " = ";
		ss << type.str() << std::endl;	

		//save pointer to the parent node in idExp
		(*var)->parentNode = varDecl;	
		Symbol *symbol = symbolTable->putSymbol(
			(*var)->name,
			CATEGORY_VAR,
			type.str(),
			*var
		);	
		
		// terminate if id already declared
		if (symbol == NULL) terminate();
		
		// save to the node
		(*var)->symbol = symbol;
		
		//TODO: resolve type if it's not defined
		//TODO: typecheck corresponding variables and expressions	
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
	if (typeDecl->typeName)
		checkTypeName(typeDecl->typeName);
	
	//check for recursive type declarations
	if(typeDecl->idExp->name.compare(typeDecl->symbolTypeToStr()) == 0) {
		std::cerr << ss.str();
		std::cerr << "Error: (line " << typeDecl->idExp->lineno
			  << ") invalid recursive type " << typeDecl->symbolTypeToStr() << std::endl;
		terminate();
	}
		
	//save pointer to the parent node in idExp
	typeDecl->idExp->parentNode = typeDecl;
	Symbol *symbol = symbolTable->putSymbol(
		typeDecl->idExp->name,
		CATEGORY_TYPE,
		typeDecl->symbolTypeToStr(),
		typeDecl->idExp
	);
	
	// terminate if id already declared
	if (symbol == NULL) terminate();
	
	// save to the node
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
	if (funcDecl->typeName)
		checkTypeName(funcDecl->typeName);

	// check if parameter types exist
	if (funcDecl->params) {
		for (auto const& param : *(funcDecl->params)) {
			checkTypeName(param->typeName);
		}
	}
	
	// save pointer to the parent node (func declaration) in the block statement,
	// so func parameters can be added to the child scope
	funcDecl->blockStmt->parentNode = funcDecl;
	funcDecl->idExp->parentNode = funcDecl;
	Symbol *symbol = symbolTable->putSymbol(
		funcDecl->idExp->name,
		CATEGORY_FUNC,
		funcDecl->symbolTypeToStr(),
		funcDecl
	);
	
	// terminate if id already declared
	if (symbol == NULL) terminate();

	// save to the node
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
	
	if (assignStmt->lhs) {
		for(auto const& exp : *(assignStmt->lhs)) {
			ASTTraversal::traverse(exp, *this);
		}
	}

	if (assignStmt->rhs) {
		for(auto const& exp : *(assignStmt->rhs)) {
			ASTTraversal::traverse(exp, *this);
		}
	}

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

void SymbolTableBuilder::visit(ForStatement *forStmt) {
	if (forStmt == NULL) return;
	
	if (isScopeOpened) {
		// open new scope
		symbolTable = symbolTable->scopeSymbolTable();
		ss << getTabs() << "{" << std::endl;
		numTabs++;

		// check init stmt
		if (forStmt->initStmt)
			ASTTraversal::traverse(forStmt->initStmt, *this);
		// check loop expression
		if (forStmt->exp)
			ASTTraversal::traverse(forStmt->exp, *this);	
		// check loop post statement
		if (forStmt->postStmt)
			ASTTraversal::traverse(forStmt->postStmt, *this);	
	} else {
		// close scope
		symbolTable = symbolTable->unscopeSymbolTable();
		numTabs--;
		ss << getTabs() << "}" << std::endl;
	}
}

void SymbolTableBuilder::visit(IfElseStatement *ifElseStmt) {	
	if (ifElseStmt == NULL) return;

	// check if expression
	if (ifElseStmt->exp)
		ASTTraversal::traverse(ifElseStmt->exp, *this);
	
	// traverse all blocks
	ASTTraversal::traverse(ifElseStmt->blockStmt, *this);
	
	if (ifElseStmt->ifStmt) {	
		ASTTraversal::traverse(ifElseStmt->ifStmt, *this);
	}
	
	if (ifElseStmt->elseBlockStmt ) {	
		ASTTraversal::traverse(ifElseStmt->elseBlockStmt, *this);
	}
}

void SymbolTableBuilder::visit(SwitchStatement *switchStmt) {
	if (switchStmt == NULL) return;
	
	symbolTable = symbolTable->scopeSymbolTable();
	ss << getTabs() << "{" << std::endl;
	numTabs++;	
	
	// check switch expression
	if (switchStmt->exp) {
		ASTTraversal::traverse(switchStmt->exp, *this);
	}

	if (switchStmt->clauseList) {
		for(auto const& clause : *(switchStmt->clauseList)) {
			if (clause->expList) {
				for(auto const& exp : *(clause->expList)) {
					ASTTraversal::traverse(exp, *this);
				}
			}
			
			if (clause->blockStmt) {
				ASTTraversal::traverse(clause->blockStmt, *this);
			}
		}
	}

	symbolTable = symbolTable->unscopeSymbolTable();
	numTabs--;
	ss << getTabs() << "}" << std::endl;
}

void SymbolTableBuilder::visit(PrintStatement *printStmt) {
	if (printStmt == NULL) return;
	
	if (printStmt->expList) {
		for(auto const& exp : *printStmt->expList) {
			ASTTraversal::traverse(exp, *this);
		}
	}
}

void SymbolTableBuilder::visit(IncDecStatement *incDecStmt) {
	if (incDecStmt == NULL) return;
	ASTTraversal::traverse(incDecStmt->exp, *this);
}

void SymbolTableBuilder::visit(ReturnStatement *returnStmt) {
	if (returnStmt == NULL) return;
	ASTTraversal::traverse(returnStmt->exp, *this);
}

void SymbolTableBuilder::visit(EmptyStatement *emptyStmt) { }

void SymbolTableBuilder::visit(ArrayExp *arrExp) {
	if (arrExp == NULL) return;

	ASTTraversal::traverse(arrExp->idExp, *this);
	
	// expr is well-typed and resolves to []T or [N]T
	checkIsArray(arrExp);
		
	// index is well-typed and resolves to int
	for(auto const& exp : *arrExp->expList) {	
		ASTTraversal::traverse(exp, *this);
		checkIsIntExp(exp);
	}

	// the result of the indexing expression is T
	arrExp->type = arrExp->idExp->type;
}

void SymbolTableBuilder::visit(BinaryOperatorExp *binOpExp) {
	if (binOpExp == NULL) return;
	
	ASTTraversal::traverse(binOpExp->lhs, *this);
	ASTTraversal::traverse(binOpExp->rhs, *this);
		
	// check if a given identifier is a type name
	// to avoid expressions with type name, i.e.: int + int
	//throw an error if such expression occurs
	if (hasTypeName(binOpExp->lhs) || hasTypeName(binOpExp->rhs)) 
		binaryExpError(
			getReceivedTypeName(binOpExp->lhs),
			getReceivedTypeName(binOpExp->rhs),	
			binOpExp->lineno
		);

	// for comparable operators
	bool isFuncLhs = false;
	bool isFuncRhs = false;	

	//check is func
	if (binOpExp->lhs->symbol) 
		isFuncLhs = binOpExp->lhs->symbol->category.compare(CATEGORY_FUNC) == 0;
	if (binOpExp->rhs->symbol) 
		isFuncRhs = binOpExp->rhs->symbol->category.compare(CATEGORY_FUNC) == 0;
	
	// resolve binary operation type
	if ( binOpExp->lhs->type.isStringType() &&     // "string"
	     binOpExp->op.compare(BINARY_PLUS) == 0 && // +
	     binOpExp->rhs->type.isStringType()        // "string"
	) binOpExp->type = TypeDescriptor(
				BASETYPE_STRING,
				BASETYPE_STRING,
				CATEGORY_CONST,
				binOpExp
			); // string concatenation
	
	else if ( binOpExp->lhs->type.isBoolType() && // bool
                  binOpExp->isBoolOperator() &&       // { ||, && }
		  binOpExp->rhs->type.isBoolType()    // bool
	) binOpExp->type = TypeDescriptor(
				BASETYPE_BOOL,
				BASETYPE_BOOL,
				CATEGORY_CONST,
				binOpExp
			); // bool type operations
	
	else if ( !isFuncLhs && // anything except func type
		  binOpExp->isComparableOperator() && // { ==, != }
		  isFuncRhs && // anything except func type
		  binOpExp->lhs->type.baseType.compare(binOpExp->rhs->type.baseType) == 0 // lhs type equals to the rhs type
	) binOpExp->type = TypeDescriptor(
				BASETYPE_BOOL,
				BASETYPE_BOOL,
				CATEGORY_CONST,
				binOpExp
			); // comparable type operations
	
	else if ( binOpExp->lhs->type.isOrderedType() && // { int, float64, string }
		  binOpExp->isOrderedOperator() &&       // { < , > , <= , >= }
		  binOpExp->rhs->type.isOrderedType()    // { int, float64, string }
	) binOpExp->type = TypeDescriptor(
				BASETYPE_BOOL,
				BASETYPE_BOOL,
				CATEGORY_CONST,
				binOpExp
			); // ordered type operations
		
	else if ( binOpExp->lhs->type.isNumericType() && // { int, float64, rune }
		  binOpExp->isNumericOperator() &&       // { + , - , * , / }
		  binOpExp->rhs->type.isNumericType()    // { int, float64, rune }
	) binOpExp->type = TypeDescriptor(
				TypeDescriptor::resolveNumericType( binOpExp->lhs->type.baseType,
								    binOpExp->rhs->type.baseType ),
				TypeDescriptor::resolveNumericType( binOpExp->lhs->type.baseType,
								    binOpExp->rhs->type.baseType ),
				CATEGORY_CONST,
				binOpExp
			); // numeric type operations
	
	else if ( binOpExp->lhs->type.isIntegerType() && // { int, rune }
		  binOpExp->isIntegerOperator() &&       // { % , | , & , << , >> , &^ , ^ }
		  binOpExp->rhs->type.isIntegerType()    // { int, rune }
	) binOpExp->type = TypeDescriptor(
				BASETYPE_INT,
				BASETYPE_INT,
				CATEGORY_CONST,
				binOpExp
			); // integer type operations	
	else {
		binaryExpError(
			binOpExp->lhs->type.name,
			binOpExp->rhs->type.name,
			binOpExp->lineno
		);
	}
}

void SymbolTableBuilder::visit(BuiltinsExp *builtinsExp) {
	if (builtinsExp == NULL) return;
}

void SymbolTableBuilder::visit(FunctionCallExp *funcCallExp) {
	if (funcCallExp == NULL) return;
		
	// copy string stream for printing errors
	symbolTable->ss.str(ss.str());
	
	ASTTraversal::traverse(funcCallExp->idExp, *this);
		
	// check if call of init func
	checkIsInitFunc(funcCallExp);
	
	// check if parameter identifiers exist in the symbol table
	if (funcCallExp->expList) {
		for(auto const& exp : *funcCallExp->expList) {
			ASTTraversal::traverse(exp, *this);
		}
	}

	// check number of arguments
	checkNumberOfFuncArgs(funcCallExp);
	
	//arg1, arg2, . . . , argk are well-typed and have types T1, T2, . . . , Tk respectively;
	checkArgTypes(funcCallExp);
	
	funcCallExp->type = funcCallExp->idExp->type; // resolve type
}

void SymbolTableBuilder::visit(IdentifierExp *idExp) {
	if (idExp == NULL) return;	
	
	Symbol *symbol = symbolTable->getSymbol(symbolTable, idExp->name);
	// check if identifier exists
	if(symbol == NULL) {
		std::cerr << ss.str();
		std::cerr << "Error: (line " << idExp->lineno << ") \""
		  << idExp->name << "\" is not declared" << std::endl;
		terminate();
	}
	
	std::stringstream type;
	   
	// if id name is the same as types/constants, wrap in braces
	if (symbol->name.compare(symbol->type) == 0)
		type << "{" << symbol->type << "}";
	else
		type << symbol->type;
		
	// save type of the id to the node
	idExp->type = TypeDescriptor(
				symbol->type,
				symbol->baseType,
				symbol->category,
				symbol->node
			);

	// save symbol pointer to the identifier expression
	idExp->symbol = symbol;
}

void SymbolTableBuilder::visit(IntegerExp *intExp) {	
	if (intExp == NULL) return;
	//set type
	intExp->type = TypeDescriptor(
				BASETYPE_INT,
				BASETYPE_INT,
				CATEGORY_TYPE,
				intExp
			);
}

void SymbolTableBuilder::visit(FloatExp *floatExp) {
	if (floatExp == NULL) return;
	//set type
	floatExp->type = TypeDescriptor(
				BASETYPE_FLOAT,
				BASETYPE_FLOAT,
				CATEGORY_TYPE,
				floatExp
			);
}

void SymbolTableBuilder::visit(RuneExp *runeExp) {
	if (runeExp == NULL) return;
	//set type
	runeExp->type = TypeDescriptor(
				BASETYPE_RUNE,
				BASETYPE_RUNE,
				CATEGORY_TYPE,
				runeExp
			);
}

void SymbolTableBuilder::visit(StringExp *strExp) {	
	if (strExp == NULL) return;
	//set type
	strExp->type = TypeDescriptor(
				BASETYPE_STRING,
				BASETYPE_STRING,
				CATEGORY_TYPE,
				strExp
			);
}

void SymbolTableBuilder::visit(BoolExp *boolExp) {	
	if (boolExp == NULL) return;
	//set type
	boolExp->type = TypeDescriptor(
				BASETYPE_BOOL,
				BASETYPE_BOOL,
				CATEGORY_TYPE,
				boolExp
			);
}

void SymbolTableBuilder::visit(UnaryExp *unaryExp) {
	if (unaryExp == NULL) return;	
	
	// check child expression
	ASTTraversal::traverse(unaryExp->exp, *this);

	bool isTypeName = hasTypeName(unaryExp->exp); // to check if a given identifier is a type name
			
	// Logical negation: expr must resolve to a bool
	if ( unaryExp->op.compare(UNARY_BANG) == 0 && 
	     (!unaryExp->exp->type.isBoolType() || isTypeName)
	) typeCompatibilityError(
			unaryExp->lineno,    // line number
			"unary op !",        // expression type
			getReceivedTypeName(unaryExp->exp),  // received type
			BASETYPE_BOOL	     // expected type
		);
	
	// Unary plus: expr must resolve to a numeric type (int, float64, rune)
	// if unary plus and expression type is NOT numeric -> throw an error		
	if ( unaryExp->op.compare(UNARY_PLUS) == 0 && 
	     (!unaryExp->exp->type.isNumericType() || isTypeName)
	) typeCompatibilityError(
			unaryExp->lineno,    // line number
			"unary op +",        // expression type
			getReceivedTypeName(unaryExp->exp),  // received type
			"numeric type (int, float64, rune)" // expected type
		);
	
	// Negation: expr must resolve to a numeric type (int, float64, rune)
	if ( unaryExp->op.compare(UNARY_MINUS) == 0 &&
	     (!unaryExp->exp->type.isNumericType() || isTypeName)
	) typeCompatibilityError(
			unaryExp->lineno,    // line number
			"unary op -",        // expression type
			getReceivedTypeName(unaryExp->exp),  // received type
			"numeric type (int, float64, rune)" // expected type
		);
	
	// Bitwise negation: expr must resolve to an integer type (int, rune)
	if ( unaryExp->op.compare(UNARY_BWXOR) == 0 && 
	     (!unaryExp->exp->type.isIntegerType() || isTypeName)
	) typeCompatibilityError(
			unaryExp->lineno,    // line number
			"unary op ^",        // expression type
			getReceivedTypeName(unaryExp->exp),  // received type
			"integer type (int, rune)" // expected type
		);
	
	//set type
	unaryExp->type = unaryExp->exp->type;
}

void SymbolTableBuilder::visit(BreakStatement *breakStmt) { }

void SymbolTableBuilder::visit(ContinueStatement *continueStmt) { }


std::string SymbolTableBuilder::getTabs() {
	std::stringstream ss;
	for(int i = 0; i < numTabs; i++) {
		ss << "\t";
	}
	return ss.str();
}

#endif
