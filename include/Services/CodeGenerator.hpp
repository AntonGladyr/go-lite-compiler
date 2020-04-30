#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP

#include <iostream>
#include <utility>
#include "Services/Visitor.hpp"
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
#include "SymbolTable/SymbolTable.hpp"
#include "AST/Expression/IdentifierExp.hpp"

class CodeGenerator : public Visitor {
	private:
		SymbolTable *symbolTable = NULL;
		unsigned int numTabs = 0;
		unsigned int initFuncNum = 0;
		bool isInversedBool = false;
		std::stringstream mainFuncCall;
		std::stringstream initFuncCalls;
		std::stringstream outCode; // for storing generated code
		int tmpVarCounter = 0;
		
		void terminate();
		void saveToFile(
			const std::string &path,
			const std::string &name,
			const std::string &ext	// extension
		);
	
	public:		
		void emit(Program *prg, SymbolTable *st);	
		void createTmpVar(VariableDeclaration *varDecl);
		void assignTmpToVarDecl(VariableDeclaration *varDecl);
		
		virtual void visit(Program *prg) override;
		virtual void visit(VariableDeclaration *varDecl) override;
		virtual void visit(TypeDeclaration *typeDecl) override;
		virtual void visit(FunctionDeclaration *funcDecl) override;
		virtual void visit(BlockStatement *blockStmt) override;
		virtual void visit(AssignStatement *assignStmt) override;
		virtual void visit(DeclarationStatement *declStmt) override;
		virtual void visit(TypeDeclarationStatement *typeDeclStmt) override;
		virtual void visit(ExpressionStatement *expStmt) override;
		virtual void visit(ForStatement *forStmt) override;
		virtual void visit(IfElseStatement *ifElseStmt) override;	
		virtual void visit(SwitchStatement *switchStmt) override;	
		virtual void visit(PrintStatement *printStmt) override;
		virtual void visit(BreakStatement *breakStmt) override;
		virtual void visit(ContinueStatement *continueStmt) override;	
		virtual void visit(IncDecStatement *incDecStmt) override;
		virtual void visit(ReturnStatement *returnStmt) override;
		virtual void visit(EmptyStatement *emptyStmt) override;
		virtual void visit(ArrayExp *arrExp) override;
		virtual void visit(BinaryOperatorExp *binOpExp) override;
		virtual void visit(BoolExp *boolExp) override;
		virtual void visit(BuiltinsExp *builtinsExp) override;
		virtual void visit(FloatExp *floatExp) override;
		virtual void visit(FunctionCallExp *funcCallExp) override;	
		virtual void visit(IdentifierExp *idExp) override;
		virtual void visit(IntegerExp *intExp) override;
		virtual void visit(RuneExp *runeExp) override;
		virtual void visit(StringExp *strExp) override;
		virtual void visit(UnaryExp *unaryExp) override;

		virtual void openScope() override { isScopeOpened = true; }
		virtual void closeScope() override { isScopeOpened = false; }
		std::string getTabs();

		CodeGenerator() { }
		~CodeGenerator() { }
};

#endif
		
