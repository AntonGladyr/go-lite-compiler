#ifndef VISITOR_HPP
#define VISITOR_HPP

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
#include "AST/Expression/Expression.hpp"
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


class Program;
class VariableDeclaration;
class TypeDeclaration;
class FunctionDeclaration;
class BlockStatement;
class DeclarationStatement;
class TypeDeclarationStatement;
class AssignStatement;
class ExpressionStatement;
class ForStatement;
class IfElseStatement;
class SwitchStatement;
class PrintStatement;
class IncDecStatement;
class BreakStatement;
class ContinueStatement;
class ReturnStatement;
class EmptyStatement;
class ArrayExp;
class BinaryOperatorExp;
class BoolExp;
class BuiltinsExp;
class FloatExp;
class FunctionCallExp;
class IdentifierExp;
class IntegerExp;
class RuneExp;
class StringExp;
class UnaryExp;

class Visitor {	
	protected:
		bool isScopeOpened = false;
	public:		
		virtual void visit(Program *prg) = 0;
		virtual void visit(VariableDeclaration *varDecl) = 0;	
		virtual void visit(TypeDeclaration *typeDecl) = 0;
		virtual void visit(FunctionDeclaration *funcDecl) = 0;
		virtual void visit(BlockStatement *blockStmt) = 0;
		virtual void visit(DeclarationStatement *declStmt) = 0;
		virtual void visit(TypeDeclarationStatement *typeDeclStmt) = 0;
		virtual void visit(AssignStatement *assignStmt) = 0;
		virtual void visit(ExpressionStatement *expStmt) = 0;
		virtual void visit(ForStatement *forStmt) = 0;
		virtual void visit(IfElseStatement *ifElseStmt) = 0;	
		virtual void visit(SwitchStatement *switchStmt) = 0;	
		virtual void visit(PrintStatement *printStmt) = 0;
		virtual void visit(BreakStatement *breakStmt) = 0;
		virtual void visit(ContinueStatement *continueStmt) = 0;
		virtual void visit(IncDecStatement *incDecStmt) = 0;
		virtual void visit(ReturnStatement *returnStmt) = 0;
		virtual void visit(EmptyStatement *emptyStmt) = 0;
		virtual void visit(ArrayExp *arrExp) = 0;
		virtual void visit(BinaryOperatorExp *binOpExp) = 0;
		virtual void visit(BoolExp *boolExp) = 0;
		virtual void visit(BuiltinsExp *builtinsExp) = 0;
		virtual void visit(FloatExp *floatExp) = 0;
		virtual void visit(FunctionCallExp *funcCallExp) = 0;	
		virtual void visit(IdentifierExp *idExp) = 0;
		virtual void visit(IntegerExp *intExp) = 0;
		virtual void visit(RuneExp *runeExp) = 0;
		virtual void visit(StringExp *strExp) = 0;
		virtual void visit(UnaryExp *unaryExp) = 0;	

		virtual void openScope() = 0;
		virtual void closeScope() = 0;
};

#endif
