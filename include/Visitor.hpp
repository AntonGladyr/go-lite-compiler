#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "Program.hpp"
//#include "TypeDeclaration.hpp"
//#include "FunctionDeclaration.hpp"
#include "IntegerExp.hpp"
#include "FloatExp.hpp"
#include "StringExp.hpp"
#include "BoolExp.hpp"
//#include "RuneExp.hpp"
#include "Expression.hpp"

class Program;
class VariableDeclaration;
class IntegerExp;
class FloatExp;
class StringExp;
class BoolExp;
//class RuneExp;
class Expression;

class Visitor {
	public:		
		virtual void visit(Program *prg) = 0;
		virtual void visit(VariableDeclaration *varDecl) = 0;
		virtual void visit(Expression *exp) = 0;
		//virtual void visit(TypeDeclaration *typeDecl) = 0;
		//virtual void visit(FunctionDeclaration *funcDecl) = 0;
		//virtual void visit(IntegerExp *intExp) = 0;
		//virtual void visit(FloatExp *floatExp) = 0;
		//virtual void visit(StringExp *strExp) = 0;
		//virtual void visit(BoolExp *boolExp) = 0;
		//TODO: virtual void visit(RuneExp *runeExp) = 0;
};

#endif
