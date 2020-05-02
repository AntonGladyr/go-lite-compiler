#ifndef CODE_GENERATOR_CPP
#define CODE_GENERATOR_CPP

#include <sstream>
#include <iostream>
#include <fstream>
#include <limits.h>
#include "Services/CodeGenerator.hpp"
#include "AST/ASTTraversal.hpp"
#include "TypeDescriptorTable/TypeDescriptorTable.hpp"
#include "Const/Constants/Constants.hpp"
#include "../helpers/vectorExtension.cpp"

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
	TypeDescriptorTable::getInstance().append("void", C_VOID);
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


void CodeGenerator::createTmpVar(VariableDeclaration *varDecl) {	
	std::vector<IdentifierExp*>::reverse_iterator varIter = varDecl->idList->rbegin();
	std::vector<Expression*>::reverse_iterator expIter;
	
	if (varDecl->expList)
		expIter = varDecl->expList->rbegin();	
		
	while (varIter != varDecl->idList->rend()) {
			
		outCode << getTabs();
		if (varDecl->typeName) {
			//outCode << TypeDescriptorTable::getInstance().getTypeDescriptor((*varIter)->symbol->baseType);
			outCode << TypeDescriptorTable::getInstance().getTypeDescriptor(varDecl->typeName->name);	
		}
		else {
			if ((*expIter)->symbol)
				outCode << (*expIter)->symbol->baseType;
			else
				outCode << TypeDescriptorTable::getInstance().getTypeDescriptor((*expIter)->type.baseType);	
		}
		
		outCode << " " << kPrefix << (*varIter)->name << "_" << kTmpVar << "_" << tmpVarCounter;
		
		// if array
		if (varDecl->typeName && varDecl->typeName->indexes) {
			for(auto const& index : *(varDecl->typeName->indexes)) {
					outCode << "[" << std::to_string(index) << "]";
			}
				
			outCode << ";" << std::endl;	
			outCode << getTabs() << "memset(" << kPrefix << (*varIter)->name
					     << "_" << kTmpVar << "_" << tmpVarCounter
					     << ", " << "0, " << "sizeof("
					     << kPrefix << (*varIter)->name
					     << "_" << kTmpVar << "_" << tmpVarCounter
					     << "));" << std::endl;
			
			(*varIter)->symbol->tmpCounterNum = tmpVarCounter;
			tmpVarCounter++;
			return;
		}
		
		outCode << " = ";
		// if expression
		if (varDecl->expList) {
			// if constant true or false
			ASTTraversal::traverse(*expIter, *this);
			/*// if binary expression
			if (typeid(BinaryOperatorExp) == typeid(*expIter))
				ASTTraversal::traverse(*expIter, *this);
			// if identifier expression
			else if (typeid(IdentifierExp) == typeid(*expIter)) {
				outCode << kPrefix << (*expIter)->toString();
			}
			else
				outCode << (*expIter)->toString();*/
		} else { // if no expression, set init value
			setVarInitValue(varDecl->typeName->name);
		}
		
		outCode << ";" << std::endl;	
		// save counter to symbol
	 	(*varIter)->symbol->tmpCounterNum = tmpVarCounter;
		//increment counter
		tmpVarCounter++;
		
		varIter++;
		if (varDecl->expList) expIter++;
	}
}

void CodeGenerator::assignTmpToVarDecl(VariableDeclaration *varDecl) {
	std::vector<IdentifierExp*>::reverse_iterator varIter = varDecl->idList->rbegin();	
	
	while (varIter != varDecl->idList->rend()) {
			
		outCode << getTabs();
		if (varDecl->typeName) {	
			outCode << TypeDescriptorTable::getInstance().getTypeDescriptor(varDecl->typeName->name);	
		} else {
			outCode << TypeDescriptorTable::getInstance().getTypeDescriptor((*varIter)->symbol->baseType);
		}
		
		outCode << " " << kPrefix << (*varIter)->name;	
		
		// if array
		if (varDecl->typeName && varDecl->typeName->indexes) {
			for(auto const& index : *(varDecl->typeName->indexes)) {
					outCode << "[" << std::to_string(index) << "]";
			}
			
			outCode << ";" << std::endl;

			outCode << getTabs() << "memcpy(" << kPrefix << (*varIter)->name
					     << ", " << kPrefix << (*varIter)->name << "_" << kTmpVar << "_"
					     << (*varIter)->symbol->tmpCounterNum
					     //<< tmpVarCounter
					     << ", NELEMS(" << kPrefix << (*varIter)->name
					     << "));" << std::endl;
			return;
		}
		
		outCode << " = ";
		outCode << kPrefix << (*varIter)->name << "_" << kTmpVar << "_" << (*varIter)->symbol->tmpCounterNum;
		
		outCode << ";" << std::endl;
		varIter++;	
	}

}

void CodeGenerator::setVarInitValue(std::string type) {
	std::string baseType = symbolTable->findBaseType(symbolTable, type);
	std::string targetType = TypeDescriptorTable::getInstance().getTypeDescriptor(baseType);
	std::stringstream initValue;
	
	if (targetType.compare(C_INT) == 0) initValue << "0";
	else if (targetType.compare(C_DOUBLE) == 0) initValue << "0.0";
	else if (targetType.compare(C_STRING) == 0) initValue << "\"\"";
	else if (targetType.compare(C_CHAR) == 0) initValue << "0";
	else if (targetType.compare(C_BOOL) == 0) initValue << "0";
	outCode << initValue.str();
}

void CodeGenerator::funcDeclToCcode(FunctionDeclaration *funcDecl) {
	std::stringstream ss;
	
	if (funcDecl->idExp->name.compare(SPECIALFUNC_INIT) == 0)
		ss << C_VOID << " " << kPrefix << funcDecl->idExp->name
		   << "__" << initFuncNum;
	else if (funcDecl->idExp->type.baseType.compare(BASETYPE_STRING) == 0)
		ss << "const " << TypeDescriptorTable::getInstance().getTypeDescriptor(funcDecl->idExp->type.baseType)
		   << " " << kPrefix << funcDecl->idExp->name;
	else if (funcDecl->idExp->type.isBaseType())
		ss << TypeDescriptorTable::getInstance().getTypeDescriptor(funcDecl->idExp->type.baseType)
	           << " " << kPrefix << funcDecl->idExp->name;
	else if (funcDecl->idExp->type.indexes) {
		ss << funcDecl->idExp->type.name << "* " << kPrefix << funcDecl->idExp->name; //TODO: multidemensional array
	}
	else	
		ss << funcDecl->idExp->type.name << " " << kPrefix << funcDecl->idExp->name;
	
	ss << "(";
	if (funcDecl->params) {
		for(auto const& param : *(funcDecl->params)) {
			// for each id print type
			std::string baseType = symbolTable->findBaseType(symbolTable, param->typeName->name);
			ss << TypeDescriptorTable::getInstance().getTypeDescriptor(baseType);
			/*if (param->idExp->symbol)
				ss << TypeDescriptorTable::getInstance().getTypeDescriptor(
					param->idExp->symbol->baseType) << " ";
			else if (param->idExp->type.isBaseType())
				ss << TypeDescriptorTable::getInstance().getTypeDescriptor(
					param->idExp->type.baseType) << " "; // base type*/
			//TODO: multidemensional array
			/*else (param->idExp->type->indexes)
				ss << */
			/*else ss << TypeDescriptorTable::getInstance().getTypeDescriptor(
					param->idExp->type.name << " "); // derived type*/
			
			ss << " " << kPrefix << param->idExp->name; // id

			if (param->typeName->indexes) {
				for(auto const& index : *(param->typeName->indexes)) {
					ss << "[" << std::to_string(index) << "]";
				}	
			}
				
			if (&param != &funcDecl->params->back())
				ss << ", ";
		}

	}
	ss << ") ";

	outCode << ss.str();
}

void CodeGenerator::printForInitStmt(Statement *initStmt) {
	if (initStmt == NULL) return;

	if (typeid(AssignStatement) == typeid(*initStmt)) {
		AssignStatement *assignStmt = (AssignStatement*)initStmt;
		
		std::vector<Expression*>::iterator lhsIter = assignStmt->lhs->begin();
		std::vector<Expression*>::iterator rhsIter = assignStmt->rhs->begin();
	
		while ( lhsIter != assignStmt->lhs->end() && rhsIter != assignStmt->rhs->end() ) {
			ASTTraversal::traverse(*lhsIter, *this);
			outCode << " = ";
			ASTTraversal::traverse(*rhsIter, *this);	
			lhsIter++;
			rhsIter++;
		}
	}
}

void CodeGenerator::printForPostStmt(Statement *postStmt) {
	if (postStmt == NULL) return;

	if (typeid(IncDecStatement) == typeid(*postStmt)) {
		IncDecStatement *incDecStmt = (IncDecStatement*)postStmt;
		
		ASTTraversal::traverse(incDecStmt->exp, *this);
	
		if (incDecStmt->op == INC_DEC_OP::INC)
			outCode << "++";

		if (incDecStmt->op == INC_DEC_OP::DEC)
			outCode << "--";
	}
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
		saveToFile(FILE_PATH, FILE_NAME, EXTENSION);
	} 
}

void CodeGenerator::visit(VariableDeclaration *varDecl) {
	if (varDecl == NULL) return;

	if (numTabs == 0) { // if global scope
		std::vector<IdentifierExp*>::reverse_iterator varIter = varDecl->idList->rbegin();
		std::vector<Expression*>::reverse_iterator expIter;
	
		if (varDecl->expList)
			expIter = varDecl->expList->rbegin();	
		
		while (varIter != varDecl->idList->rend()) {
			
			outCode << getTabs();
			
			/*
			// if true or false
			if ( (*varIter)->name.compare(CONSTANT_TRUE) &&
			     
			) {
				outCode << CONSTANT_TRUE
			}

			if ((*varIter)->name.compare(CONSTANT_FALSE)) {
				outCode << 
			}*/
			
			if (varDecl->typeName) {
				//outCode << TypeDescriptorTable::getInstance().getTypeDescriptor((*varIter)->symbol->baseType);
				outCode << TypeDescriptorTable::getInstance().getTypeDescriptor(varDecl->typeName->name);	
			}
			else {
				if ((*expIter)->symbol)
					outCode << (*expIter)->symbol->baseType;
				else
					outCode << TypeDescriptorTable::getInstance().getTypeDescriptor((*expIter)->type.baseType);	
			}
		
			outCode << " " << kPrefix << (*varIter)->name;
		
			// if array
			if (varDecl->typeName && varDecl->typeName->indexes) {
				for(auto const& index : *(varDecl->typeName->indexes)) {
						outCode << "[" << std::to_string(index) << "]";
				}
				
				outCode << ";" << std::endl;
				/*outCode << getTabs() << "memset(" << kPrefix << (*varIter)->name
						     << ", " << "0, " << "sizeof("
						     << kPrefix << (*varIter)->name
						     << "));" << std::endl;*/
				return;
			}
		
			outCode << " = ";
			// if expression
			if (varDecl->expList) {	
				if (typeid(BinaryOperatorExp) == typeid(*expIter) || typeid(IdentifierExp) == typeid(*expIter)){	
					ASTTraversal::traverse(*expIter, *this);
				}
				else {	
					outCode << (*expIter)->toString();
				}
			} else { // if no expression, set init value
				setVarInitValue(varDecl->typeName->name);
			}
		
			outCode << ";" << std::endl;	
			
			varIter++;
			if (varDecl->expList) expIter++;
		}

	} else {
		createTmpVar(varDecl);
		assignTmpToVarDecl(varDecl);
	}

	outCode << std::endl;
}

void CodeGenerator::visit(TypeDeclaration *typeDecl) {
	if (typeDecl == NULL) return;
}

void CodeGenerator::visit(FunctionDeclaration *funcDecl) {
	if (funcDecl == NULL) return;

	funcDeclToCcode(funcDecl);

	if (funcDecl->idExp->name.compare(SPECIALFUNC_INIT) == 0) {
		initFuncCalls << funcDecl->initCallToCcode(initFuncNum);
		initFuncNum++;
	}

	if (funcDecl->idExp->name.compare(SPECIALFUNC_MAIN) == 0)
		mainFuncCall << funcDecl->mainCallToCCode();
}

void CodeGenerator::visit(BlockStatement *blockStmt) {
	if (blockStmt == NULL) return;
	
	if (isScopeOpened) {
		outCode << "{" << std::endl;
		numTabs++;
	} else {
		numTabs--;
		outCode << getTabs() << "}" << std::endl << std::endl;
	}
}

void CodeGenerator::visit(ExpressionStatement *expStmt) {
	if (expStmt == NULL) return;
	
	ASTTraversal::traverse(expStmt->exp, *this);
	outCode << std::endl;
}

void CodeGenerator::visit(DeclarationStatement *declStmt) {	
	if (declStmt == NULL) return;
	ASTTraversal::traverse(declStmt->decl, *this);
}

void CodeGenerator::visit(TypeDeclarationStatement *typeDeclStmt) {
	if (typeDeclStmt == NULL) return;	
}

void CodeGenerator::visit(AssignStatement *assignStmt) {
	if (assignStmt == NULL) return;
	
	std::vector<Expression*>::iterator lhsIter = assignStmt->lhs->begin();
	std::vector<Expression*>::iterator rhsIter = assignStmt->rhs->begin();
	
	while ( lhsIter != assignStmt->lhs->end() && rhsIter != assignStmt->rhs->end() ) {
		ASTTraversal::traverse(*lhsIter, *this);
		outCode << " = ";
		ASTTraversal::traverse(*rhsIter, *this);
		outCode << ";" << std::endl;
		lhsIter++;
		rhsIter++;
	}
}

void CodeGenerator::visit(ForStatement *forStmt) {
	if (forStmt == NULL) return;
	
	if (isScopeOpened) {	
	
		if ( forStmt->initStmt == NULL &&
		     forStmt->exp == NULL &&
		     forStmt->postStmt == NULL 
		) {
			outCode << getTabs() << "for(;;) ";
		}
		else if ( forStmt->initStmt == NULL &&
			  forStmt->exp &&
			  forStmt->postStmt == NULL
		) {
			outCode << getTabs() << "while(";
			ASTTraversal::traverse(forStmt->exp, *this);
			outCode << ") ";
		}
		else if ( forStmt->initStmt &&
			  forStmt->exp &&
			  forStmt->postStmt
		) {	
			outCode << getTabs() << "for (";
			printForInitStmt(forStmt->initStmt);
			outCode << "; ";
			//ASTTraversal::traverse(forStmt->initStmt, *this);
			ASTTraversal::traverse(forStmt->exp, *this);
			outCode << "; ";
			printForPostStmt(forStmt->postStmt);
			//ASTTraversal::traverse(forStmt->postStmt, *this);
			outCode << ") ";
		}
	}
}

void CodeGenerator::visit(IfElseStatement *ifElseStmt) {	
	if (ifElseStmt == NULL) return;
	
	outCode << getTabs() << "if (";
	ASTTraversal::traverse(ifElseStmt->exp, *this);
	outCode << ") ";
	
	ASTTraversal::traverse(ifElseStmt->blockStmt, *this);
	
	if (ifElseStmt->ifStmt) {
		outCode << getTabs() << "else ";
		ASTTraversal::traverse(ifElseStmt->ifStmt, *this);
	}
	
	if (ifElseStmt->elseBlockStmt ) {
		outCode << getTabs() << "else ";
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
	
	//std::stringstream ss;
	//ss << ", "; // expressions to print
	
	outCode << getTabs() << "printf(";
	outCode << "\"";
	
	//specifiers
	for(auto const& exp: *(printStmt->expList)) {
		if (exp->symbol) {
			if (exp->symbol->baseType.compare(BASETYPE_STRING) == 0)
				outCode << "%s";
			else if (exp->symbol->baseType.compare(BASETYPE_INT) == 0)
				outCode << "%d";
			else if (exp->symbol->baseType.compare(BASETYPE_RUNE) == 0)
				outCode << "%d";
			else if (exp->symbol->baseType.compare(BASETYPE_FLOAT) == 0)
				outCode << "%+e";
			else if (exp->symbol->baseType.compare(BASETYPE_BOOL) == 0) {
				outCode << "%s";	
				//ss << "(" << kPrefix << exp->toString() << " ? \"true\" : \"false\")";
			}
		}
		else {
			if (exp->type.baseType.compare(BASETYPE_STRING) == 0)
				outCode << "%s";
			else if (exp->type.baseType.compare(BASETYPE_INT) == 0)
				outCode << "%d";
			else if (exp->type.baseType.compare(BASETYPE_RUNE) == 0)
				outCode << "%d";
			else if (exp->type.baseType.compare(BASETYPE_FLOAT) == 0)
				outCode << "%+e";
			else if (exp->type.baseType.compare(BASETYPE_BOOL) == 0) {
				outCode << "%s";	
				//ss << "(" << kPrefix << exp->toString() << " ? \"true\" : \"false\")";
			}
		}
			
		if (printStmt->isPrintln && exp != printStmt->expList->back()) {
			outCode << " ";
		}
	
		if (printStmt->isPrintln && exp == printStmt->expList->back()) {
			outCode << "\\n";
		}
	}
	
	outCode << "\"";
	outCode << ", "; // expressions to print
	
	//values
	for(auto const& exp: *(printStmt->expList)) {	
		//if not bool expression, copy the value
		if (exp->type.baseType.compare(BASETYPE_BOOL) == 0) {
			if ( exp->toString().compare(CONSTANT_TRUE) == 0 ||
			     exp->toString().compare(CONSTANT_FALSE) == 0
			) outCode << "(" << exp->toString() << " ? \"true\" : \"false\")";
			else if (typeid(BinaryOperatorExp) == typeid(*exp) && exp->type.baseType.compare(BASETYPE_BOOL) == 0) {
				outCode << "(";
				ASTTraversal::traverse(exp, *this);
				outCode << " ? \"true\" : \"false\"";
				outCode << ")";
			}
			else
				outCode << "(" << kPrefix << exp->toString() << " ? \"true\" : \"false\")";
		}
		else if (exp->type.baseType.compare(BASETYPE_BOOL) != 0 && typeid(IdentifierExp) == typeid(*exp))
			//ss << kPrefix << exp->toString();
			ASTTraversal::traverse(exp, *this);
		else if (exp->type.baseType.compare(BASETYPE_BOOL) != 0 && typeid(BinaryOperatorExp) == typeid(*exp))
			ASTTraversal::traverse(exp, *this);
		else if (exp->type.baseType.compare(BASETYPE_BOOL) != 0 && typeid(ArrayExp) == typeid(*exp))
			ASTTraversal::traverse(exp, *this);
		else if (exp->type.baseType.compare(BASETYPE_BOOL) != 0 && typeid(ArrayExp) == typeid(*exp))
			outCode << kPrefix << exp->toString();
		else if (exp->type.baseType.compare(BASETYPE_BOOL) != 0 && typeid(IdentifierExp) != typeid(*exp))
			outCode << exp->toString();
		
		if (exp != printStmt->expList->back()) outCode << ", ";
	}
	
	//outCode << ss.str();
	//if (printStmt->expList) outCode << ", " << *(printStmt->expList);
	
	outCode << ");" << std::endl;	
}

void CodeGenerator::visit(BreakStatement *breakStmt) {
	if (breakStmt == NULL) return;
	outCode << getTabs() << "break;" << std::endl;
}

void CodeGenerator::visit(ContinueStatement *continueStmt) {
	if (continueStmt == NULL) return;
	outCode << getTabs() << "continue;" << std::endl;
}

void CodeGenerator::visit(IncDecStatement *incDecStmt) {
	if (incDecStmt == NULL) return;	
	
	outCode << getTabs();
	
	ASTTraversal::traverse(incDecStmt->exp, *this);
	
	if (incDecStmt->op == INC_DEC_OP::INC)
		outCode << "++";

	if (incDecStmt->op == INC_DEC_OP::DEC)
		outCode << "--";

	outCode << ";" << std::endl;
}

void CodeGenerator::visit(ReturnStatement *returnStmt) {
	if (returnStmt == NULL) return;
	outCode << getTabs() << "return ";
	ASTTraversal::traverse(returnStmt->exp, *this);
	outCode << ";" << std::endl;
}

void CodeGenerator::visit(EmptyStatement *emptyStmt) {
	if (emptyStmt == NULL) return;	
}

void CodeGenerator::visit(ArrayExp *arrExp) {
	if (arrExp == NULL) return;
	outCode << getTabs() << kPrefix << arrExp->idExp->name;
	for(auto const& exp: *(arrExp->expList)) {
		if ( typeid(IdentifierExp) == typeid(*exp) ||
		     typeid(BinaryOperatorExp) == typeid(*exp)
		) {
			outCode << "[";
			ASTTraversal::traverse(exp, *this);
			outCode << "]";
		}
		else outCode << "[" << exp->toString() << "]";
	}
}

void CodeGenerator::visit(BinaryOperatorExp *binOpExp) {
	if (binOpExp == NULL) return;
	//outCode << "(";
	/*if (typeid(IdentifierExp) == typeid(binOpExp->lhs))
		outCode << kPrefix << binOpExp->lhs->toString();
	else outCode << binOpExp->lhs->toString();*/
		
	//get id declaration
	
	/*if ( binOpExp->lhs->symbol && binOpExp->rhs->symbol &&
	     typeid(IdentifierExp) == typeid(binOpExp->lhs->symbol->node) &&
	     typeid(IdentifierExp) == typeid(binOpExp->rhs->symbol->node) &&
	     binOpExp->op.compare(BINARY_EQUAL) == 0
	) {	
		std::cout << "test" << std::endl;
		Symbol *symbLhs = symbolTable->getSymbol(symbolTable, lhs->name);
		Symbol *symbRhs = symbolTable->getSymbol(symbolTable, rhs->name);
		IdentifierExp *lhs = (IdentifierExp*)binOpExp->lhs;
		IdentifierExp *rhs = (IdentifierExp*)binOpExp->rhs;
		VariableDeclaration *varLhs = (VariableDeclaration*)s1->node;
		VariableDeclaration *varRhs = (VariableDeclaration*)s2->node;	
		if (varLhs->typeName->indexes && varRhs->typeName->indexes) {
			outCode << "ARRAY_CMP(" << lhs->name << ", " << rhs->name << ") == 0"; 
			return;
		}
	}*/
	
	ASTTraversal::traverse(binOpExp->lhs, *this);
	outCode << " " << binOpExp->op << " ";
	ASTTraversal::traverse(binOpExp->rhs, *this);
	/*if (typeid(IdentifierExp) == typeid(binOpExp->rhs))
		outCode << kPrefix << binOpExp->rhs->toString();
	else outCode << binOpExp->rhs->toString();*/
	//outCode << ")";
}

void CodeGenerator::visit(BoolExp *boolExp) {
	if (boolExp == NULL) return;
}

void CodeGenerator::visit(BuiltinsExp *builtinsExp) {
	if (builtinsExp == NULL) return;

	if (builtinsExp->name.compare(BUILTIN_CAP) == 0) {
		//TODO: outCode << "sizeof("
	}

	if ( builtinsExp->name.compare(BUILTIN_LEN) == 0 && 
	     typeid(IdentifierExp) == typeid(builtinsExp->exp)
	) {
		IdentifierExp *idExp = (IdentifierExp*)builtinsExp->exp;
		outCode << "sizeof(" << idExp->name << ") / sizeof(*" << idExp->name << ")";
	}

	if ( builtinsExp->name.compare(BUILTIN_LEN) == 0 && 
	     typeid(StringExp) == typeid(builtinsExp->exp)
	) {
		outCode << "sizeof(" << builtinsExp->exp << ") / sizeof(char)";
	}
}

void CodeGenerator::visit(FloatExp *floatExp) {
	if (floatExp == NULL) return;
	outCode << floatExp->value;
}

void CodeGenerator::visit(FunctionCallExp *funcCallExp) {
	if (funcCallExp == NULL) return;
	
	// if typecasting call
	if ( funcCallExp->idExp->symbol->category.compare(CATEGORY_TYPE) == 0 ) {
		std::string baseType = symbolTable->findBaseType(symbolTable, funcCallExp->idExp->symbol->type);
		outCode << TypeDescriptorTable::getInstance().getTypeDescriptor(baseType); //type
		outCode << "(";

		for(auto const& exp : *(funcCallExp->expList)) {
			/*if (typeid(IdentifierExp) == typeid(*exp))
				outCode << kPrefix << exp->toString();
			else outCode << exp->toString();*/
			
			if (typeid(BinaryOperatorExp) == typeid(*exp) || typeid(IdentifierExp) == typeid(*exp))
				ASTTraversal::traverse(exp, *this);
			else
				outCode << exp->toString();
			if (&exp != &funcCallExp->expList->back())
				outCode << ", ";
		}

		outCode << ");";
		/*outCode << funcCallExp->idExp->symbol->baseType << "("
		    << *(funcCallExp->expList) << ")";*/
		return;
	}
	
	outCode << getTabs() << kPrefix << funcCallExp->idExp->name;
	
	outCode << "(";
	
	for(auto const& exp : *(funcCallExp->expList)) {
		/*if (typeid(IdentifierExp) == typeid(*exp))
			outCode << kPrefix << exp->toString();
		else outCode << exp->toString();*/
		if (typeid(BinaryOperatorExp) == typeid(*exp) || typeid(IdentifierExp) == typeid(*exp))
			ASTTraversal::traverse(exp, *this);
		else 
			outCode << exp->toString();
		
		if (&exp != &funcCallExp->expList->back())
			outCode << ", ";
	}
	
	outCode << ");";
}

void CodeGenerator::visit(IdentifierExp *idExp) {
	if (idExp == NULL) return;	
	
	//if constant false or true
	if ( idExp->name.compare(CONSTANT_TRUE) == 0 ||
	     idExp->name.compare(CONSTANT_FALSE) == 0
	) outCode << idExp->name;
	else
		outCode << kPrefix << idExp->name;
}

void CodeGenerator::visit(IntegerExp *intExp) {
	if (intExp == NULL) return;
	outCode << intExp->value;
}

void CodeGenerator::visit(RuneExp *runeExp) {
	if (runeExp == NULL) return;
	outCode << "'" << runeExp->value << "'";
}

void CodeGenerator::visit(StringExp *strExp) {
	if (strExp == NULL) return;	
	outCode << "\"" << strExp->value << "\"";
}

void CodeGenerator::visit(UnaryExp *unaryExp) {
	if (unaryExp == NULL) return;

	// Logical negation: expr must resolve to a bool
	if ( unaryExp->op.compare(UNARY_BANG) == 0 ) {
		outCode << unaryExp->op;
		ASTTraversal::traverse(unaryExp->exp, *this);
	}

	 // Unary plus: expr must resolve to a numeric type (int, float64, rune)
	if ( unaryExp->op.compare(UNARY_PLUS) == 0 ) {
		ASTTraversal::traverse(unaryExp->exp, *this);
	}

	// Negation: expr must resolve to a numeric type (int, float64, rune)
	if ( unaryExp->op.compare(UNARY_MINUS) == 0 ) {
		outCode << unaryExp->op;
		ASTTraversal::traverse(unaryExp->exp, *this);
	}

	// Bitwise negation: expr must resolve to an integer type (int, rune)
	if ( unaryExp->op.compare(UNARY_BWXOR) == 0 ) {
		if (unaryExp->exp->type.baseType.compare(BASETYPE_INT)) {
			outCode << INT_MAX << " " << unaryExp->op << " ";
			ASTTraversal::traverse(unaryExp->exp, *this);
		}

		if (unaryExp->exp->type.baseType.compare(BASETYPE_RUNE)) {
			outCode << CHAR_MAX << " " << unaryExp->op << " ";
			ASTTraversal::traverse(unaryExp->exp, *this);
		}
	}
}

std::string CodeGenerator::getTabs() {
	std::stringstream ss;
	for(int i = 0; i < numTabs; i++) {
		ss << "\t";
	}
	return ss.str();
}

#endif
