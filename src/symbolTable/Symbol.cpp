#ifndef SYMBOL_CPP
#define SYMBOL_CPP

#include <sstream>
#include <string>
#include "SymbolTable/Symbol.hpp"

std::string Symbol::toString() { }

Symbol::~Symbol() {
	delete node;
	node = NULL;
	delete next;
	next = NULL;
}

#endif
