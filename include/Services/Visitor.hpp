#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "AST/Program/Program.hpp"
#include "AST/Declaration/VariableDeclaration.hpp"
#include "AST/Declaration/TypeDeclaration.hpp"
#include "AST/Declaration/FunctionDeclaration.hpp"
#include "AST/Statement/BlockStatement.hpp"
#include "AST/Statement/ReturnStatement.hpp"
#include "AST/Statement/EmptyStatement.hpp"
#include "AST/Expression/Expression.hpp"

class Program;
class VariableDeclaration;
class TypeDeclaration;
class FunctionDeclaration;
class BlockStatement;
class ReturnStatement;
class EmptyStatement;

class Visitor {	
	protected:
		bool isScopeOpened = false;
	public:		
		virtual void visit(Program *prg) = 0;
		virtual void visit(VariableDeclaration *varDecl) = 0;	
		virtual void visit(TypeDeclaration *typeDecl) = 0;
		virtual void visit(FunctionDeclaration *funcDecl) = 0;
		virtual void visit(BlockStatement *blockStmt) = 0;
		virtual void visit(ReturnStatement *returnStmt) = 0;
		virtual void visit(EmptyStatement *emptyStmt) = 0;

		virtual void openScope() = 0;
		virtual void closeScope() = 0;	
};

#endif
