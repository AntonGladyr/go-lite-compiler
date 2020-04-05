#ifndef FUNCTIONPARAMETER_CPP
#define FUNCTIONPARAMETER_CPP

#include "AST/Declaration/FunctionParameter.hpp"

FunctionParameter::~FunctionParameter() {
	delete idExp;
	delete type;
}

#endif
