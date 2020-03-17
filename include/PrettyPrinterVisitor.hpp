#ifndef PRETTYPRINTERVISITOR_HPP
#define PRETTYPRINTERVISITOR_HPP


#include <iostream>
#include <utility>
#include "Visitor.hpp"

class PrettyPrinterVisitor : public Visitor {
    public:
	PrettyPrinterVisitor() { }

	virtual void visit(Program *prg) override;
};

#endif
