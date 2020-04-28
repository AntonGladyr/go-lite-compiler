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
		//std::cout << outCode.str() << std::endl;
		saveToFile(FILE_PATH, FILE_NAME, EXTENSION);
	} 
}

void CodeGenerator::visit(VariableDeclaration *varDecl) {
	if (varDecl == NULL) return;
	
	std::vector<IdentifierExp*>::reverse_iterator varIter = varDecl->idList->rbegin();
	std::vector<Expression*>::reverse_iterator expIter;
	if (varDecl->expList)
		expIter = varDecl->expList->rbegin();
	
	while (varIter != varDecl->idList->rend()) {
		
		outCode << getTabs();
		if (varDecl->typeName) {	
			outCode << TypeDescriptorTable::getInstance().getTypeDescriptor((*varIter)->symbol->baseType);
			
			if (varDecl->typeName->indexes) {
				for(auto const& index : *(varDecl->typeName->indexes)) {
					outCode << "[" << std::to_string(index) << "]";
				}
			}
		}
		else {
			if ((*expIter)->symbol)
				outCode << (*expIter)->symbol->baseType;
			else
				outCode << TypeDescriptorTable::getInstance().getTypeDescriptor((*expIter)->type.baseType);
		}
		
		outCode << " " << (*varIter)->name;
	
		if (varDecl->expList) {
			outCode << " = ";
			ASTTraversal::traverse(*expIter, *this);
		}
		
		outCode << ";" << std::endl;
		varIter++;
		if (varDecl->expList) expIter++;
	}	
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
	
	if (isScopeOpened) {
		outCode << getTabs() << "{" << std::endl;
		numTabs++;
	} else {
		numTabs--;
		outCode << getTabs() << "}" << std::endl << std::endl;
	}
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

void CodeGenerator::visit(ExpressionStatement *expStmt) {
	if (expStmt == NULL) return;
	
}

void CodeGenerator::visit(ForStatement *forStmt) {
	if (forStmt == NULL) return;
		
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
		//TODO: fix new line
		outCode << getTabs() << "for (";
		ASTTraversal::traverse(forStmt->initStmt, *this);
		ASTTraversal::traverse(forStmt->exp, *this);
		ASTTraversal::traverse(forStmt->postStmt, *this);
		outCode << getTabs() << ") ";
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
	
	std::string space;
	
	if (printStmt->isPrintln) space = " ";
	else space = "";

	outCode << getTabs() << "printf(\"";

	for(auto const& exp: *(printStmt->expList)) {
		if (exp->symbol) {
			if (exp->symbol->baseType.compare(BASETYPE_STRING) == 0)
				outCode << "%s" << space;
			else if (exp->symbol->baseType.compare(BASETYPE_INT) == 0)
				outCode << "%d" << space;
			else if (exp->symbol->baseType.compare(BASETYPE_RUNE) == 0)
				outCode << "%c" << space; 
			else if (exp->symbol->baseType.compare(BASETYPE_FLOAT) == 0)
				outCode << "%f" << space;
			else if (exp->symbol->baseType.compare(BASETYPE_BOOL) == 0) //TODO:fix for bool
				outCode << "%d" << space;
		}
		else {
			if (exp->type.baseType.compare(BASETYPE_STRING) == 0)
				outCode << "%s" << space;
			else if (exp->type.baseType.compare(BASETYPE_INT) == 0)
				outCode << "%d" << space;
			else if (exp->type.baseType.compare(BASETYPE_RUNE) == 0)
				outCode << "%c" << space;
			else if (exp->type.baseType.compare(BASETYPE_FLOAT) == 0)
				outCode << "%f" << space;
			else if (exp->type.baseType.compare(BASETYPE_BOOL) == 0) //TODO:fix for bool
				outCode << "%d" << space;
		}
	}

	outCode << "\"";
	if (printStmt->expList) outCode << ", " << *(printStmt->expList);
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
		outCode << "++;";

	if (incDecStmt->op == INC_DEC_OP::DEC)
		outCode << "--;";

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
	outCode << arrExp->idExp->name;
	for(auto const& exp: *(arrExp->expList)) {
		outCode << "[" << exp->toString() << "]";
	}
}

void CodeGenerator::visit(BinaryOperatorExp *binOpExp) {
	if (binOpExp == NULL) return;
	outCode << "(";
	ASTTraversal::traverse(binOpExp->lhs, *this);
	outCode << " " << binOpExp->op << " ";
	ASTTraversal::traverse(binOpExp->rhs, *this);
	outCode << ")";
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
		outCode << funcCallExp->idExp->symbol->baseType << "("
		    << *(funcCallExp->expList) << ")";
		return;
	}
	
	outCode << funcCallExp->idExp->name << "("
		<< *(funcCallExp->expList) << ")";
}

void CodeGenerator::visit(IdentifierExp *idExp) {
	if (idExp == NULL) return;
	outCode << idExp->name;
}

void CodeGenerator::visit(IntegerExp *intExp) {
	if (intExp == NULL) return;
	outCode << intExp->value;
}

void CodeGenerator::visit(RuneExp *runeExp) {
	if (runeExp == NULL) return;
	outCode << runeExp->value;
}

void CodeGenerator::visit(StringExp *strExp) {
	if (strExp == NULL) return;
	outCode << strExp->value;
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
