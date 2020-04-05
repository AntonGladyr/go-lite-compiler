#ifndef TYPENAME_CPP
#define TYPENAME_CPP

#include "AST/Declaration/TypeName.hpp"

TypeName::~TypeName() {
	delete indexes;
}

#endif
