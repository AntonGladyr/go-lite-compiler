#ifndef SYMBOLTABLEBUILDER_HPP
#define SYMBOLTABLEBUILDER_HPP

#include <iostream>
#include <sstream>
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
#include "AST/Expression/IdentifierExp.hpp"
#include "SymbolTable/SymbolTable.hpp"
#include "AST/Declaration/TypeName.hpp"

class SymbolTable;

class SymbolTableBuilder : public Visitor {
	private:
		Program *program = NULL;
		SymbolTable *symbolTable = NULL;
		unsigned int numTabs = 0;
		std::stringstream ss; // for printing symbol table
		bool isSymbolMode;
		
		void terminate();
		void checkTypeName(TypeName *type);
		void insertFuncParams(Node *node);
		void checkSpecialFunctions(Node *node);
		void checkIdName(Node *node); // check identifier name ('main' and 'init' must be a function)	
		void checkIsInitFunc(FunctionCallExp *funcCallExp);
		void checkNumberOfFuncArgs(FunctionCallExp *funcCallExp);
		void checkArgTypes(FunctionCallExp *funcCallExp);	
		void checkIsIntExp(Expression *exp);
		void checkBuiltinCap(BuiltinsExp *builtinsExp);
		void checkBuiltinLen(BuiltinsExp *builtinsExp);
		void checkClauseExp(Expression *clauseExp, Expression *switchExp);
		void checkTypeConversion(FunctionCallExp *funcCallExp);
		void checkVoidFunc(Expression *exp);
		void checkIfFuncExist(Expression *exp);
		void checkIfFuncName(Expression *lhs, Expression *rhs);
		void checkReturnAtEndOfFunc(Statement *stmt);
		void checkIsFuncType(FunctionCallExp *funcCallExp);
		void checkLvalues(std::vector<Expression*> *lhs);
		void checkAssignTypes(Expression *lhs, Expression *rhs);
		bool hasBreakInIfStmt(Statement *ifStmt);
		void typeCompatibilityError(
			int lineno,
			const std::string &expName,
			const std::string &receivedType,
			const std::string &expectedType
		);
		void arrayIndexingError(ArrayExp *arrExp);
		void binaryExpError(
			const std::string &lhsType,
			const std::string &rhsType,
			int lineno
		);
		TypeDescriptor resolveArrayExpType(ArrayExp *arrExp);
		bool hasTypeName(Expression *exp);
		std::string getReceivedTypeName(Expression *exp);
		
	public:	
		SymbolTable *build(Program *prg, bool _isSymbolMode);
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
		
		SymbolTableBuilder() { } 
		~SymbolTableBuilder() { }
};

#endif	
