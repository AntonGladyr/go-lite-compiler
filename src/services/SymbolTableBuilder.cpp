#ifndef SYMBOLTABLEBUILDER_CPP
#define SYMBOLTABLEBUILDER_CPP

#include <iostream>
#include "Services/SymbolTableBuilder.hpp"
#include "SymbolTable/SymbolTable.hpp"
#include "SymbolTable/Symbol.hpp"
#include "AST/ASTTraversal.hpp"

// initializes a symbol table
SymbolTable *SymbolTableBuilder::build(Program *prg, bool _isSymbolMode) {
	//copy program pointer for deallocation
	program = prg;
	isSymbolMode = _isSymbolMode;

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

//TODO: possibly move all helper functions to a separate class

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
	if (typeid(FunctionDeclaration) == typeid(*node)) {
		FunctionDeclaration *funcDecl = (FunctionDeclaration*)node;

		// return false if not "main" nor "init"
		if ((funcDecl->idExp->name.compare(SPECIALFUNC_MAIN) != 0) &&
				(funcDecl->idExp->name.compare(SPECIALFUNC_INIT) != 0)) return;

		if(funcDecl->typeName || funcDecl->params) {
			if (isSymbolMode) std::cerr << ss.str();
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
		if (isSymbolMode) std::cerr << ss.str();
		std::cerr << "Error: (line " << type->lineno << ") type \""
			<< type->name << "\" is not declared" << std::endl;	
		terminate();
	}

	// check if identifier has "type" category
	if (s->category.compare(CATEGORY_TYPE) != 0) {
		if (isSymbolMode) std::cerr << ss.str();
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
		if (isSymbolMode) std::cerr << ss.str();
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
		if (isSymbolMode) std::cerr << ss.str();
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

	if ( (funcCallExp->expList == NULL || funcCallExp->expList->size() == 0) &&
	     (funcDecl->params == NULL || funcDecl->params->size() == 0)	
	) return;
		
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
	
	if (funcCallExp->expList == NULL || funcCallExp->expList->size() == 0) return;

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

// if function call id is not a CATEGORY_FUNC, throw an error
void SymbolTableBuilder::checkIfFuncExist(Expression *exp) {	
	if ( exp == NULL ||
	     typeid(FunctionCallExp) != typeid(*exp)
	) return;	
	
	FunctionCallExp *funcCall = (FunctionCallExp*)exp;
	Symbol *s = symbolTable->getSymbol(symbolTable, funcCall->idExp->name);

	if (s == NULL) {
		std::cerr << "Error: (line " << funcCall->idExp->lineno << ") "
			  << funcCall->idExp->name << "is not declared" << std::endl;
		terminate();
	}

	if (s->category.compare(CATEGORY_FUNC) != 0) {
		std::cerr << "Error: (line " << funcCall->idExp->lineno << ") "
			  << "cannot call non-function " << funcCall->idExp->name << std::endl;
		terminate();
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

void SymbolTableBuilder::checkIsIntExp(Expression *exp) {
	IdentifierExp *idExp = NULL;

	if (typeid(IdentifierExp) == typeid(*exp)) {
		idExp = (IdentifierExp*)exp;

		// if id name is "int"
		if (idExp->name.compare(BASETYPE_INT) == 0) {
			std::cerr << "Error: (line " << exp->lineno << ") "
				<< "index must be an int "
				<< "[received " << getReceivedTypeName(exp) << "]" << std::endl;
			terminate();
		}
	}

	if (exp->type.baseType.compare(BASETYPE_INT) != 0) {
		std::cerr << "Error: (line " << exp->lineno << ") "
			<< "index must be an int "
			<< "[received " << getReceivedTypeName(exp) << "]" << std::endl;
		terminate();
	}
}

// A cap expression is well-typed if expr is well-typed, has type S and S resolves to [N]T
void SymbolTableBuilder::checkBuiltinCap(BuiltinsExp *builtinsExp) {
	if ( !builtinsExp->exp->type.isArray() ) {
	  	std::cerr << "Error: (line " << builtinsExp->exp->lineno << ") "
	  		  << "capacity builtin expects slice or array type as argument "
	  		  << "[received " << builtinsExp->exp->type.name << "]" << std::endl;
	  	terminate();
	  }
}

// A len expression is well-typed if expr is well-typed, has type S and S resolves to string or [N]T
void SymbolTableBuilder::checkBuiltinLen(BuiltinsExp *builtinsExp) {
	if ( !builtinsExp->exp->type.isArray() &&
	  	builtinsExp->exp->type.baseType.compare(BASETYPE_STRING) != 0
	  ) {
	  	std::cerr << "Error: (line " << builtinsExp->exp->lineno << ") "
	  	    	  << "length builtin expects slice, array or string type as argument "
	  	    	  << "[received " << builtinsExp->exp->type.name << "]" << std::endl;
		terminate();
	  }
}

void SymbolTableBuilder::checkClauseExp(Expression *clauseExp, Expression *switchExp) {
	// a switch statement without an expression
	if ( switchExp == NULL &&
	     !hasTypeName(clauseExp) && 
	     clauseExp->type.name.compare(BASETYPE_BOOL) == 0
	) return;
	// a switch statement with an expression
	else if ( switchExp && 
		  !hasTypeName(switchExp) &&
		  !hasTypeName(clauseExp) &&
		  switchExp->type.name.compare(clauseExp->type.name) == 0
	) return;
	else {
		std::stringstream switchExpType;
		if (switchExp) switchExpType << switchExp->type.name;
		else switchExpType << BASETYPE_BOOL;
		
		std::cerr << "Error: (line " << clauseExp->lineno << ") "
			  << "switch statement expresion type is incompatible with case type "
			  << "[" << getReceivedTypeName(clauseExp) << " != "
			  << switchExpType.str() << "]" << std::endl;
		terminate();
	}
}

// throws an error if an expression cannot be cast
void SymbolTableBuilder::checkTypeConversion(FunctionCallExp *funcCallExp) {
	if ( funcCallExp->expList == NULL ||
	     funcCallExp->expList->size() == 0 ||
	     funcCallExp->expList->size() > 1
	) {
		std::cerr << "Error: (line " << funcCallExp->idExp->lineno << ") "
			  << "conversion expects 1 argument" << std::endl;
		terminate();
	}
	
	bool isTypeName = hasTypeName(funcCallExp->expList->front());

	// type and expr resolve to identical underlying types;
	bool isIdenticalBaseTypes = 
		(funcCallExp->idExp->type.baseType.compare(funcCallExp->expList->front()->type.baseType) == 0);

	// type and expr both resolve to numeric types;
	bool isBothNumericTypes = 
		(funcCallExp->idExp->type.isNumericType() && funcCallExp->expList->front()->type.isNumericType());	

	// type resolves to a string type and expr resolves to an integer type (rune or int)
	bool isStringAndInt = 
		(funcCallExp->idExp->type.isStringType() && funcCallExp->expList->front()->type.isIntegerType());	

	if ( !isTypeName &&
	     ( isIdenticalBaseTypes || 
	       isBothNumericTypes ||
	       isStringAndInt
	     )
	) return;
	else {
		std::cerr << "Error: (line " << funcCallExp->idExp->lineno << ") "
			  << "conversion between incompatible types "
			  << "[" << funcCallExp->idExp->name << "<-" 
			  << getReceivedTypeName(funcCallExp->expList->front()) << "]" << std::endl;
		terminate();
	}
}

// check if a variable assigns to main() function call
void SymbolTableBuilder::checkVoidFunc(Expression *exp) {
	if (exp == NULL) return;
	
	if (typeid(FunctionCallExp) != typeid(*exp)) return;

	FunctionCallExp *funcCall = (FunctionCallExp*)exp;
	if ( funcCall->idExp->name.compare(SPECIALFUNC_MAIN) == 0 ||
	     funcCall->idExp->type.name.compare("void") == 0
	) {
		std::cerr << "Error: (line " << funcCall->idExp->lineno << ") "
		  	  << "void cannot be used as a value in variable declaration" << std::endl;
		terminate();
	}
}

// check if a variable uses a function name
void SymbolTableBuilder::checkIfFuncName(Expression *lhs, Expression *rhs) {
	if (lhs == NULL && rhs == NULL) return;
		
	if (lhs != NULL && typeid(IdentifierExp) == typeid(*lhs)) {
		IdentifierExp *idLhs = (IdentifierExp*)lhs;
		if (idLhs->name.empty()) return;
		Symbol *s = symbolTable->getSymbol(symbolTable, idLhs->name);	
		
		if (s->category.compare(CATEGORY_FUNC) == 0) {	
			std::cerr << "Error: (line " << idLhs->lineno << ") "
			  	  << getReceivedTypeName(lhs) << " is not assignment compatible" << std::endl;
			terminate();
		}
	}
	     
	if (rhs != NULL && typeid(IdentifierExp) != typeid(*rhs)) {
		IdentifierExp *idRhs = (IdentifierExp*)rhs;
		if (idRhs->name.empty()) return;
		Symbol *s = symbolTable->getSymbol(symbolTable, idRhs->name);
		if (s->category.compare(CATEGORY_FUNC) == 0) {
			std::cerr << "Error: (line " << idRhs->lineno << ") "
			  	  << getReceivedTypeName(rhs) << " is not assignment compatible" << std::endl; 
			terminate();
		}
	}
}

// throws an error if the given expression is not an array
void SymbolTableBuilder::arrayIndexingError(ArrayExp *arrExp) {	
	std::cerr << "Error: (line " << arrExp->lineno << ") "
		<< "indexing target expects list target (slice, array) "
		<< "[received " << getReceivedTypeName(arrExp->idExp)
		<< "]" << std::endl;
	terminate();
}

// resolves array expression type
TypeDescriptor SymbolTableBuilder::resolveArrayExpType(ArrayExp *arrExp) {
	IdentifierExp *idExp = NULL;
	VariableDeclaration *varDecl = NULL;
	FunctionDeclaration *funcDecl = NULL;

	Symbol *s = symbolTable->getSymbol(symbolTable, arrExp->idExp->name);	

	// if the given node is not an identifier thow an error
	if (typeid(IdentifierExp) != typeid(*(s->node)))
		arrayIndexingError(arrExp);

	idExp = (IdentifierExp*)s->node;

	// if parent node of the given identifier is not a VariableDeclaration node, throw an error
	if (typeid(VariableDeclaration) != typeid(*(idExp->parentNode)))
		arrayIndexingError(arrExp);

	varDecl = (VariableDeclaration*)idExp->parentNode;

	// if a variable declaration does not have any indexes in the type, throw an error
	if (varDecl->typeName->indexes == NULL)
		arrayIndexingError(arrExp);

	return TypeDescriptor(
			varDecl->typeName->name,
			symbolTable->findBaseType(symbolTable, varDecl->typeName->name),
			CATEGORY_VAR,
			varDecl
			);
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


std::string SymbolTableBuilder::getTabs() {
	std::stringstream ss;
	for(int i = 0; i < numTabs; i++) {
		ss << "\t";
	}
	return ss.str();
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
	
	/* 
	   var x T        => Adds the mapping x:T to the symbol table.
	   var x T = expr => If expr is well-typed and its type is T1, and T1=T, the mapping x:T is added to the symbol
			     table.
	   var x = expr   => If expr is well-typed and its type is T, the mapping x:T is added to the symbol table.
	*/

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
	
	std::vector<IdentifierExp*>::reverse_iterator varIter = varDecl->idList->rbegin();
	std::vector<Expression*>::reverse_iterator expIter; 
	if (varDecl->expList)
		expIter = varDecl->expList->rbegin();
	
	// reverse iteration for identifiers
	//for (auto var = varDecl->idList->rbegin(); var != varDecl->idList->rend(); var++) {
	while (varIter != varDecl->idList->rend()) {
		std::stringstream type;
			
		if (varDecl->expList) {
			// check if a variable assigns to main() function call throw an error
			checkVoidFunc(*expIter);
		}
		
		// check if a variable name is not 'main' nor 'init'
		// (parent->parent scope => basetypes)
		if (symbolTable->parent->parent == NULL) checkIdName(*varIter);
		
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
			
			// if type is specified, save it to each identifier
			//TODO: modify find base type for arrays
			(*varIter)->type = TypeDescriptor(
				type.str(),
				type.str(),
				CATEGORY_VAR,
				varDecl->typeName->indexes,
				*varIter
			);
		}
		// if type of a var declaration is not specified, use expression type
		else if (!varDecl->typeName && *expIter) {
			type << (*expIter)->type.name;
		}
		else {
			type << BASETYPE_UNDEFINED;
		}
		
		ss << getTabs() << (*varIter)->name << " [" << CATEGORY_VAR << "]" << " = ";
		ss << type.str() << std::endl;	
		
		//save pointer to the parent node in idExp
		(*varIter)->parentNode = varDecl;	
		Symbol *symbol = symbolTable->putSymbol(
			(*varIter)->name,
			CATEGORY_VAR,
			type.str(),
			*varIter
		);
		
		// terminate if id already declared
		if (symbol == NULL) terminate();
		
		// save to the node
		(*varIter)->symbol = symbol;	
			
		// resolve type if it's not defined
		if ( varDecl->typeName == NULL )
			(*varIter)->type = (*expIter)->type;
		
		// typecheck corresponding variables and expressions; check if an expression is a type name
		if ( (varDecl->expList && (*varIter)->type.baseType.compare((*expIter)->type.baseType) != 0) ||
			  (varDecl->expList && hasTypeName(*expIter) )
		) {
			std::cerr << "Error: (line " << (*expIter)->lineno << ") "
				  << getReceivedTypeName(*expIter) << " is not assignment compatible with "
				  << (*varIter)->type.name << " in variable declaration" << std::endl;
			terminate();
		}
		
		varIter++;
		if (varDecl->expList) expIter++;
	}
}

void SymbolTableBuilder::visit(TypeDeclaration *typeDecl) {
	if (typeDecl == NULL) return;
	
	/*
	  type T1 T2
	  Adds the type mapping T1 -> def(T2) to the type symbol table (i.e., T1 is a defined type inheriting from T2)
	  If T1 is already declared in the current scope, an error is raised. If T1 is already declared, but in an outer
	  scope, the new T1 -> def(T2) type mapping will shadow the previous mapping
	*/
	
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
		if (isSymbolMode) std::cerr << ss.str();
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
	
	/*
	  func f(p1 T1, p2 T2, ..., pn Tn) Tr {
		// statements
	  }

	  Given the declaration for f above, the mapping f:(T1 * T2 * ... * Tn -> Tr) is added to the symbol table. 
	  If f is already declared in the current scope (i.e. the global scope since we don’t have nested functions),
	  an error is raised.
	*/

	// copy string stream for printing errors
	symbolTable->ss.str(ss.str());

	// check special functions: init and main
	checkSpecialFunctions(funcDecl);
	
	// return if init function
	if (funcDecl->idExp->name.compare(SPECIALFUNC_INIT) == 0) {	
		ss << getTabs() << funcDecl->symbolToStr() << std::endl;
		return;
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

	// check if parameter types exist
	if (funcDecl->params) {
		for (auto const& param : *(funcDecl->params)) {
			checkTypeName(param->typeName);
		}
	}
		
	std::vector<int> *indexes = NULL;

	// check if return type exists
	if (funcDecl->typeName) {
		checkTypeName(funcDecl->typeName);
		
		indexes = funcDecl->typeName->indexes;
	}
		
	// save type
	funcDecl->idExp->type = TypeDescriptor(
					funcDecl->symbolTypeToStr(),
					funcDecl->symbolTypeToStr(),	
					CATEGORY_FUNC,
					indexes,
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
	
	/*
	   A block type checks if its statements type check. A block opens a new scope in the symbol table.
	*/
	
	if (isScopeOpened) {
		// open new scope
		symbolTable = symbolTable->scopeSymbolTable();
		
		ss << getTabs() << "{" << std::endl;
		numTabs++;
		
		// if parent node is FuncDecl, put func parameters to the symbol table
		if ( blockStmt->parentNode &&
		     typeid(FunctionDeclaration) == typeid(*(blockStmt->parentNode))
		) {	
			insertFuncParams(blockStmt->parentNode);
			FunctionDeclaration *funcDecl = (FunctionDeclaration*)blockStmt->parentNode;
			blockStmt->functionNode = funcDecl;
		}
		
		// save pointer to the base (function) block in each statement
		if (blockStmt->stmtList) {	
			for(auto &stmt : *(blockStmt->stmtList)) {	
				stmt->functionNode = blockStmt->functionNode;
			}	
		}

		// save pointer to the function in block and return statements
		
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

	/*
	   v1, v2, ..., vk = e1, e2, ..., en
	   An assignment statement type checks if:
	   - All the expressions on the left-hand side are well-typed;
	   - All the expressions on the right-hand side are well-typed;
	   - For every pair of lvalue/expression, typeof(vi) = typeof(ei) (no resolving).
	*/
	
	if (assignStmt->lhs) {
		for(auto const& exp : *(assignStmt->lhs)) {
			ASTTraversal::traverse(exp, *this);
		}
	}

	if (assignStmt->rhs) {
		for(auto const& exp : *(assignStmt->rhs)) {
			ASTTraversal::traverse(exp, *this);

			// check if a variable assigns to main() function call throw an error
			checkVoidFunc(exp);
		}
	}
	
	checkAssignEquality(assignStmt->lhs->size(), assignStmt->rhs->size(), assignStmt);

	std::vector<Expression*>::iterator lhsIter = assignStmt->lhs->begin();
	std::vector<Expression*>::iterator rhsIter = assignStmt->rhs->begin();
		
	while ( lhsIter != assignStmt->lhs->end() && rhsIter != assignStmt->rhs->end() ) {	
		if ( hasTypeName(*lhsIter) ||
		     hasTypeName(*rhsIter) ||
		     (*lhsIter)->type.name.compare((*rhsIter)->type.name) != 0
		) {
			std::cerr << "Error: (line " << (*lhsIter)->lineno << ") "
			  	  << getReceivedTypeName(*rhsIter) << " is not assignment compatible with "
				  << getReceivedTypeName(*lhsIter) << " in assign statement" << std::endl;
			terminate();
		}
	
		// check if function name used as an identifier
		//checkIfFuncName(*lhsIter, *rhsIter);
		
		lhsIter++;
		rhsIter++;
	}
}

void SymbolTableBuilder::visit(ExpressionStatement *expStmt) {
	if (expStmt == NULL) return;
	
	/*
	   expr
	   An expression statement is well-typed if its expression child is well-typed. In GoLite, only function call
	   expressions are allowed to be used as statements, i.e. foo(x, y) can be used as a statement, but x-1 cannot.
	*/
	
	// if a given expression is not a function call, throw an error	
	if (typeid(FunctionCallExp) != typeid(*(expStmt->exp))) {
		if (isSymbolMode) std::cerr << ss.str();
		std::cerr << "Error: (line " << expStmt->exp->lineno << ") "
			  << "expression statement must be a function call" << std::endl;
		terminate();
	} else {	
		FunctionCallExp *funcCall = (FunctionCallExp*)expStmt->exp;
		Symbol *s = symbolTable->getSymbol(symbolTable, funcCall->idExp->name);
		
		if (s == NULL) {
			std::cerr << "Error: (line " << funcCall->idExp->lineno << ") "
				  << "function " << funcCall->idExp->name << " is not declared" << std::endl;
			terminate();
		}
		
		if (hasTypeName(funcCall->idExp)) {
			if (isSymbolMode) std::cerr << ss.str();
			std::cerr << "Error: (line " << expStmt->exp->lineno << ") "
			  	  << "expression statement must be a function call" << std::endl;
			terminate();
		}
	}
	
	ASTTraversal::traverse(expStmt->exp, *this);
}

void SymbolTableBuilder::visit(ForStatement *forStmt) {
	if (forStmt == NULL) return;

	/*
	   for {
		// statements
	   }
	   An infinite for loop type checks if its body type checks. The body opens a new scope in the symbol table.

	   for expr {
		// statements
	   }
	   A "while" loop type checks if:
		- Its expression is well-typed and resolves to type bool;
		- The statements type check.

	   for init; expr; post {
		// statements
	   }
	   three-part for loop type checks if:
		- init type check;
		- expr is well-typed and resolves to type bool;
		- post type checks;
		- the statements type check.
	*/
	
	if (isScopeOpened) {
		// open new scope
		symbolTable = symbolTable->scopeSymbolTable();
		ss << getTabs() << "{" << std::endl;
		numTabs++;

		// check init stmt
		if (forStmt->initStmt)
			ASTTraversal::traverse(forStmt->initStmt, *this);
	
		// check loop expression
		if (forStmt->exp) {	
			ASTTraversal::traverse(forStmt->exp, *this);
			if ( !forStmt->exp->type.isBoolType() ||
			     hasTypeName(forStmt->exp)
			) {
				std::cerr << "Error: (line " << forStmt->exp->lineno << ") "
					  << "incompatible type in loop condition "
					  << "[received " << getReceivedTypeName(forStmt->exp) << ", expected "
					  << BASETYPE_BOOL << "]" << std::endl;
				terminate();
			}
		}
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

	/*
	   if expr {
	   	// then statements
	   } else {
	   	// else statements
	   }

	   An if statement type checks if:
		- expr is well-typed and resolves to type bool;
		- The statements in the first block type check;
		- The statements in the second block type check.
	*/

	// check if expression
	if (ifElseStmt->exp) {
		ASTTraversal::traverse(ifElseStmt->exp, *this);

		checkVoidFunc(ifElseStmt->exp);
		
		if ( !ifElseStmt->exp->type.isBoolType() ||
		     hasTypeName(ifElseStmt->exp)
		) {
			std::cerr << "Error: (line " << ifElseStmt->exp->lineno << ") "
				  << "incompatible type in if condition "
				  << "[received " << getReceivedTypeName(ifElseStmt->exp)
				  << ", expected " << BASETYPE_BOOL << "]" << std::endl;
			terminate();
		}
	}
	
	// traverse all blocks
	ifElseStmt->blockStmt->functionNode = ifElseStmt->functionNode;
	ASTTraversal::traverse(ifElseStmt->blockStmt, *this);
	
	if (ifElseStmt->ifStmt) {
		ifElseStmt->ifStmt->functionNode = ifElseStmt->functionNode;
		ASTTraversal::traverse(ifElseStmt->ifStmt, *this);
	}
	
	if (ifElseStmt->elseBlockStmt) {
		ifElseStmt->elseBlockStmt->functionNode = ifElseStmt->functionNode;
		ASTTraversal::traverse(ifElseStmt->elseBlockStmt, *this);
	}
}

void SymbolTableBuilder::visit(SwitchStatement *switchStmt) {
	if (switchStmt == NULL) return;

	/*
	   switch expr {
	   case e1, e2, ..., en:
	   	// statements
	   default:
	   	// statements
	   }

	   A switch statement with an expression type checks if:
		- expr is well-typed and is a comparable type;
		- The expressions e1, e2, . . . , en are well-typed and have the same type as expr;
		- The statements under the different alternatives type check.

	   switch {
	   case e1, e2, ..., en:
		// statements
	   default:
		// statements
	   }
	   
	   A switch statement without an expression type checks if:
		- The expressions e1, e2, . . . , en are well-typed and have type bool;
		- The statements under the different alternatives type check.
	*/
	
	symbolTable = symbolTable->scopeSymbolTable();
	ss << getTabs() << "{" << std::endl;
	numTabs++;	
	
	// check switch expression
	if (switchStmt->exp) {
		ASTTraversal::traverse(switchStmt->exp, *this);

		checkVoidFunc(switchStmt->exp);

		// for comparable operators
		bool isFunc = false;	

		//check is func
		if (switchStmt->exp->symbol) 
			isFunc = switchStmt->exp->symbol->category.compare(CATEGORY_FUNC) == 0;
		
		if ( isFunc ||
		     hasTypeName(switchStmt->exp)
		) {
			std::cerr << "Error: (line " << switchStmt->exp->lineno << ") "
				  << "slice, map, and function values are not comparable" << std::endl
				  << "[received " << getReceivedTypeName(switchStmt->exp)
				  << ", expected comparable type" << "]" << std::endl;
			terminate();
		}
	}	

	if (switchStmt->clauseList) {
		for(auto const& clause : *(switchStmt->clauseList)) {
			if (clause->expList) {
				for(auto const& exp : *(clause->expList)) {
					ASTTraversal::traverse(exp, *this);
					checkClauseExp(exp, switchStmt->exp);
				}
			}
			
			if (clause->blockStmt) {
				clause->blockStmt->functionNode = switchStmt->functionNode;
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
	
	/*
	   print(e1, ..., ek)
	   println(e1, ..., ek)
	   
	   A print statement type checks if all its expressions are well-typed and resolve to a base type
	   (int, float64, bool, string, rune).
	*/
	
	if (printStmt->expList) {
		for(auto const& exp : *printStmt->expList) {
			ASTTraversal::traverse(exp, *this);	
			// all expressions must resolve to a base type (int, float64, bool, string, rune)
			if ( exp->type.name.empty() ||
			     hasTypeName(exp) ||
			     !exp->type.isBaseType()
			) {	
				std::cerr << "Error: (line " << exp->lineno << ") "
					  << "print expects base types "
				          << "[received " << getReceivedTypeName(exp) << "]" << std::endl;
				terminate();
			}	
		}
	}
}

void SymbolTableBuilder::visit(IncDecStatement *incDecStmt) {
	if (incDecStmt == NULL) return;
	
	/*
	   expr++
	   expr--

	   An increment/decrement statement type checks if its expression is well-typed and resolves to a numeric
	   base type (int, float64, rune).
	*/

	ASTTraversal::traverse(incDecStmt->exp, *this);

	if ( !incDecStmt->exp->type.isNumericType() ||
	     typeid(IdentifierExp) != typeid(*(incDecStmt->exp)) || 
	     hasTypeName(incDecStmt->exp)
	) {
		std::stringstream opName;
		if (incDecStmt->op == INC_DEC_OP::INC) opName << "increment";
		else if (incDecStmt->op == INC_DEC_OP::DEC) opName << "decrement";
		
		std::cerr << "Error: (line " << incDecStmt->exp->lineno << ") "
			  << " incompatible type in " << opName.str()
			  << " [received " << getReceivedTypeName(incDecStmt->exp)
			  << ", expected numeric (int, rune, float64)]" << std::endl;
		terminate();
	}
}

void SymbolTableBuilder::visit(ReturnStatement *returnStmt) {
	if (returnStmt == NULL) return;
	
	/*
	   return
	   A return statement with no expression is well-typed if the enclosing function has no return type.
	
	   return expr
	   A return statement with an expression is well-typed if its expression is well-typed and the type
	   of this expression is the same as the return type of the enclosing function.
	*/

	ASTTraversal::traverse(returnStmt->exp, *this);	

	//TODO: weeding pass

	if ( returnStmt->functionNode == NULL ) {
		std::cerr << "Error: (line " << returnStmt->lineno << ") " << std::endl; //TODO: write error
		terminate();
	}
		
	FunctionDeclaration *funcDecl = (FunctionDeclaration*)returnStmt->functionNode;	

	bool funcHasType = funcDecl->typeName != NULL;

	if ( returnStmt->exp == NULL && funcHasType ) {
		std::cerr << "Error: (line " << returnStmt->lineno << ") "
			  << "invalid return [function has non-void return type]" << std::endl;
		terminate();
	}	

	if ( returnStmt->exp && !funcHasType ) {
		std::cerr << "Error: (line " << returnStmt->lineno << ") "
			  << "invalid return [function has void return type]" << std::endl;
		terminate();
	}

	if ( funcHasType && // if a function has a type
	     returnStmt->exp && // and return statement has an expression
	     returnStmt->exp->type.name.compare(funcDecl->symbolTypeToStr()) != 0 ) { // compare both types
	     std::cerr << "Error: (line " << returnStmt->exp->lineno << ") "
			  << funcDecl->symbolTypeToStr() << " is not assignment compatible with "
			  << returnStmt->exp->type.name << " in return statement" << std::endl;
		terminate();
	}	

}

void SymbolTableBuilder::visit(EmptyStatement *emptyStmt) { }

void SymbolTableBuilder::visit(ArrayExp *arrExp) {
	if (arrExp == NULL) return;

	ASTTraversal::traverse(arrExp->idExp, *this);	
		
	// index is well-typed and resolves to int
	for(auto const& exp : *arrExp->expList) {	
		ASTTraversal::traverse(exp, *this);
		checkIsIntExp(exp);
	}
	
	// expr is well-typed and resolves to []T or [N]T
	// the result of the indexing expression is T	
	arrExp->type = resolveArrayExpType(arrExp);
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
				binOpExp->lhs->type.name,
				BASETYPE_BOOL,
				CATEGORY_CONST,
				binOpExp
			); // bool type operations
	
	else if ( !isFuncLhs && // anything except func type
		  binOpExp->isComparableOperator() && // { ==, != }
		  !isFuncRhs && // anything except func type
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
				binOpExp->lhs->type.name,
				TypeDescriptor::resolveNumericType( binOpExp->lhs->type.baseType,
								    binOpExp->rhs->type.baseType ),
				CATEGORY_CONST,
				binOpExp
			); // numeric type operations
	
	else if ( binOpExp->lhs->type.isIntegerType() && // { int, rune }
		  binOpExp->isIntegerOperator() &&       // { % , | , & , << , >> , &^ , ^ }
		  binOpExp->rhs->type.isIntegerType()    // { int, rune }
	) binOpExp->type = TypeDescriptor(
				binOpExp->lhs->type.name,
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
	
	ASTTraversal::traverse(builtinsExp->exp, *this);	

	if (builtinsExp->name.compare(BUILTIN_CAP) == 0) {
		checkBuiltinCap(builtinsExp);
		builtinsExp->type = TypeDescriptor(
					BASETYPE_INT,
					BASETYPE_INT,
					CATEGORY_FUNC,
					builtinsExp
				);
		return;
	}
	
	if (builtinsExp->name.compare(BUILTIN_LEN) == 0) {
		checkBuiltinLen(builtinsExp);
		builtinsExp->type = TypeDescriptor(
					BASETYPE_INT,
					BASETYPE_INT,
					CATEGORY_FUNC,
					builtinsExp
				);
		return;
	}	
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
	
	// if typecasting call
	// 'type' resolves to a base type int, float64, bool, rune or string;
	if ( hasTypeName(funcCallExp->idExp) &&
	     baseTypesList.find(funcCallExp->idExp->type.baseType) != baseTypesList.end()) {
		/*
		   expr is well-typed and has a type that can be be cast to type:
			- type and expr resolve to identical underlying types;
			- type and expr both resolve to numeric types;
			- type resolves to a string type and expr resolves to an integer type (rune or int)

		   The type of a type cast expression is 'type'
		*/
		
		checkTypeConversion(funcCallExp);
		
		// resolve type
		//TODO: fix base type
		funcCallExp->type = TypeDescriptor(
					funcCallExp->idExp->name,
					funcCallExp->idExp->name,
					CATEGORY_VAR,
					funcCallExp
				);

		return;
	}
	
	// if function call id is not a CATEGORY_FUNC, throw an error
	checkIfFuncExist(funcCallExp);
	
	// check if call of init func
	checkIsInitFunc(funcCallExp);
	
	// check number of arguments
	checkNumberOfFuncArgs(funcCallExp);

	//arg1, arg2, . . . , argk are well-typed and have types T1, T2, . . . , Tk respectively;
	checkArgTypes(funcCallExp);

	// resolve type
	FunctionDeclaration *funcDecl = (FunctionDeclaration*)funcCallExp->idExp->symbol->node;

	funcCallExp->type = funcDecl->idExp->type;
}

void SymbolTableBuilder::visit(IdentifierExp *idExp) {
	if (idExp == NULL) return;	
	
	Symbol *symbol = symbolTable->getSymbol(symbolTable, idExp->name);
	// check if identifier exists
	if(symbol == NULL) {
		if (isSymbolMode) std::cerr << ss.str();
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
	
	std::vector<int> *indexes = NULL;
	
	// save type of the id to the node
	idExp->type = TypeDescriptor(
				symbol->type,
				symbol->baseType,
				symbol->category,
				indexes,
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

#endif
