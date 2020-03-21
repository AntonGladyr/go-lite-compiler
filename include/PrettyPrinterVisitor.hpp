#ifndef PRETTYPRINTERVISITOR_HPP
#define PRETTYPRINTERVISITOR_HPP


#include <iostream>
#include <utility>
#include "Visitor.hpp"
#include "Program.hpp"
#include "VariableDeclaration.hpp"
#include "IntegerExp.hpp"

class PrettyPrinterVisitor : public Visitor {
    public:
	PrettyPrinterVisitor() { }
	
	virtual void visit(Program *prg) override;
	virtual void visit(VariableDeclaration *varDecl) override;
	
	virtual void visit(IntegerExp *intExp) override;
	virtual void visit(FloatExp *floatExp) override;
	virtual void visit(StringExp *strExp) override;
	virtual void visit(BoolExp *boolExp) override;
};

#endif
