#ifndef ASTTRAVERSAL_CPP
#define ASTTRAVERSAL_CPP

#include <typeinfo>   // operator typeid
#include "AST/ASTTraversal.hpp"
#include "AST/Program/Program.hpp"
#include "AST/Declaration/VariableDeclaration.hpp"
#include "AST/Declaration/TypeDeclaration.hpp"
#include "AST/Declaration/FunctionDeclaration.hpp"
#include "AST/Statement/BlockStatement.hpp"
#include "AST/Statement/DeclarationStatement.hpp"
#include "AST/Statement/TypeDeclarationStatement.hpp"
#include "AST/Statement/AssignStatement.hpp"
#include "AST/Statement/ExpressionStatement.hpp"
#include "AST/Statement/ForStatement.hpp"
#include "AST/Statement/IfElseStatement.hpp"
#include "AST/Statement/SwitchStatement.hpp"
#include "AST/Statement/PrintStatement.hpp"
#include "AST/Statement/BreakStatement.hpp"
#include "AST/Statement/ContinueStatement.hpp"
#include "AST/Statement/IncDecStatement.hpp"
#include "AST/Statement/ReturnStatement.hpp"
#include "AST/Statement/EmptyStatement.hpp"
#include "AST/Expression/ArrayExp.hpp"
#include "AST/Expression/BinaryOperatorExp.hpp"
#include "AST/Expression/BoolExp.hpp"
#include "AST/Expression/BuiltinsExp.hpp"
#include "AST/Expression/Expression.hpp"
#include "AST/Expression/FloatExp.hpp"
#include "AST/Expression/FunctionCallExp.hpp"
#include "AST/Expression/IdentifierExp.hpp"
#include "AST/Expression/IntegerExp.hpp"
#include "AST/Expression/RuneExp.hpp"
#include "AST/Expression/StringExp.hpp"
#include "AST/Expression/UnaryExp.hpp"


void ASTTraversal::traverse(Node *node, Visitor& visitor) {
	if (node == NULL) return;
	if (typeid(Program) == typeid(*node)) {
		Program *prg = (Program*)node;
		visitor.openScope();
		prg->accept(visitor);
		
		if (prg->declList) {	
			for(auto const& decl : *(prg->declList)) {	
				traverse(decl, visitor);	
			}
		}
		
		visitor.closeScope();
		prg->accept(visitor);
		return;
	}
	
	if (typeid(VariableDeclaration) == typeid(*node)) {	
		VariableDeclaration *varDecl = (VariableDeclaration*)node;
		varDecl->accept(visitor);
	}

	if (typeid(TypeDeclaration) == typeid(*node)) {
		TypeDeclaration *typeDecl = (TypeDeclaration*)node;
		typeDecl->accept(visitor);	
	}

	if (typeid(FunctionDeclaration) == typeid(*node)) {
		FunctionDeclaration *funcDecl = (FunctionDeclaration*)node;
		funcDecl->accept(visitor);	
		traverse(funcDecl->blockStmt, visitor);	
	}
	
	if (typeid(BlockStatement) == typeid(*node)) {
		BlockStatement *blockStmt = (BlockStatement*)node;
		visitor.openScope();
		blockStmt->accept(visitor);
		if (blockStmt->stmtList) {	
			for(auto const& stmt : *(blockStmt->stmtList)) {	
				traverse(stmt, visitor);
			}
		}
		visitor.closeScope();
		blockStmt->accept(visitor);
	}

	if (typeid(DeclarationStatement) == typeid(*node)) {
		DeclarationStatement *declStmt = (DeclarationStatement*)node;
		declStmt->accept(visitor);
	}

	if (typeid(TypeDeclarationStatement) == typeid(*node)) {
		TypeDeclarationStatement *typeDeclStmt = (TypeDeclarationStatement*)node;
		typeDeclStmt->accept(visitor);
	}

	if (typeid(AssignStatement) == typeid(*node)) {
		AssignStatement *assignStmt = (AssignStatement*)node;
		assignStmt->accept(visitor);
	}

	if (typeid(ExpressionStatement) == typeid(*node)) {
		ExpressionStatement *expStmt = (ExpressionStatement*)node;
		expStmt->accept(visitor);
	}

	if (typeid(ForStatement) == typeid(*node)) {
		ForStatement *forStmt = (ForStatement*)node;
		visitor.openScope();
		forStmt->accept(visitor);
		traverse(forStmt->blockStmt, visitor);
		visitor.closeScope();
		forStmt->accept(visitor);
	}

	if (typeid(IfElseStatement) == typeid(*node)) {
		IfElseStatement *ifElseStmt = (IfElseStatement*)node;
		ifElseStmt->accept(visitor);
	}

	if(typeid(SwitchStatement) == typeid(*node)) {	
		SwitchStatement *switchStmt = (SwitchStatement*)node;
		switchStmt->accept(visitor);
	}

	if (typeid(PrintStatement) == typeid(*node)) {
		PrintStatement *printStmt = (PrintStatement*)node;
		printStmt->accept(visitor);
	}

	if (typeid(BreakStatement) == typeid(*node)) {
		BreakStatement *breakStmt = (BreakStatement*)node;
		breakStmt->accept(visitor);
	}

	if (typeid(ContinueStatement) == typeid(*node)) {
		ContinueStatement *continueStmt = (ContinueStatement*)node;
		continueStmt->accept(visitor);
	}

	if (typeid(IncDecStatement) == typeid(*node)) {
		IncDecStatement *incDecStmt = (IncDecStatement*)node;
		incDecStmt->accept(visitor);
	}

	if (typeid(ReturnStatement) == typeid(*node)) {	
		ReturnStatement *returnStmt = (ReturnStatement*)node;
		returnStmt->accept(visitor);
	}

	if (typeid(EmptyStatement) == typeid(*node)) {
		EmptyStatement *emptyStmt = (EmptyStatement*)node;
		emptyStmt->accept(visitor);
	}

	if (typeid(ArrayExp) == typeid(*node)) {
		ArrayExp *arrayExp = (ArrayExp*)node;
		arrayExp->accept(visitor);
	}

	if (typeid(BinaryOperatorExp) == typeid(*node)) {
		BinaryOperatorExp *binOpExp = (BinaryOperatorExp*)node;
		binOpExp->accept(visitor);
	}

	if (typeid(BoolExp) == typeid(*node)) {
		BoolExp *boolExp = (BoolExp*)node;
		boolExp->accept(visitor);
	}

	if (typeid(BuiltinsExp) == typeid(*node)) {
		BuiltinsExp *builtinsExp = (BuiltinsExp*)node;
		builtinsExp->accept(visitor);
	}

	if (typeid(FloatExp) == typeid(*node)) {
		FloatExp *floatExp = (FloatExp*)node;
		floatExp->accept(visitor);
	}
	
	if (typeid(FunctionCallExp) == typeid(*node)) {
		FunctionCallExp *funcCall = (FunctionCallExp*)node;
		funcCall->accept(visitor);
	}

	if (typeid(IdentifierExp) == typeid(*node)) {
		IdentifierExp *idExp = (IdentifierExp*)node;
		idExp->accept(visitor);
	}

	if (typeid(IntegerExp) == typeid(*node)) {
		IntegerExp *intExp = (IntegerExp*)node;
		intExp->accept(visitor);
	}

	if (typeid(RuneExp) == typeid(*node)) {
		RuneExp *runeExp = (RuneExp*)node;
		runeExp->accept(visitor);
	}

	if (typeid(StringExp) == typeid(*node)) {
		StringExp *strExp = (StringExp*)node;
		strExp->accept(visitor);
	}

	if (typeid(UnaryExp) == typeid(*node)) {
		UnaryExp *unaryExp = (UnaryExp*)node;
		unaryExp->accept(visitor);
	}
}

#endif
