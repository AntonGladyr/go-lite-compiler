#ifndef PRETTYPRINTER_HPP
#define PRETTYPRINTER_HPP

#include <iostream>
#include <utility>
#include "Services/Visitor.hpp"
#include "AST/Program/Program.hpp"
#include "AST/Declaration/VariableDeclaration.hpp"
#include "AST/Declaration/TypeDeclaration.hpp"
#include "AST/Declaration/FunctionDeclaration.hpp"

class PrettyPrinter : public Visitor {
    public:
	PrettyPrinter() { }
	
	virtual void visit(Program *prg) override;
	virtual void visit(VariableDeclaration *varDecl) override;
	virtual void visit(TypeDeclaration *typeDecl) override;
	virtual void visit(FunctionDeclaration *funcDecl) override;		
};

#endif
