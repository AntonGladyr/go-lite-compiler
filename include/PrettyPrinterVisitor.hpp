#ifndef PRETTYPRINTERVISITOR_HPP
#define PRETTYPRINTERVISITOR_HPP


#include <iostream>
#include <utility>
#include "Visitor.hpp"
#include "Program.hpp"
#include "VariableDeclaration.hpp"

class PrettyPrinterVisitor : public Visitor {
    public:
	PrettyPrinterVisitor() { }
	
	virtual void visit(Program *prg) override;
	virtual void visit(VariableDeclaration *varDecl) override;
};

#endif
