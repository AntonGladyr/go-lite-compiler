#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <string>
#include <sstream>
#include <vector>
#include "SymbolTable/Symbol.hpp"
#include "SymbolTable/HashFunction.h"
#include "AST/Node.hpp"

class SymbolTable {	
	public:
		Symbol *table[HashSize] = {};
		SymbolTable *parent = NULL;
		SymbolTable *headParent = NULL; // keep the top parent for memory deallocation
		// keep pointers to the child scopes for memory deallocation
		std::vector<SymbolTable*> childList;
		std::stringstream ss; // for printing symbol table

		SymbolTable *scopeSymbolTable();
		SymbolTable *unscopeSymbolTable();
		Symbol *putSymbol(	
			const std::string &name,
			const std::string &category,
			const std::string &type,
			Node *node
		);
		
		Symbol *getSymbol(SymbolTable *t, const std::string &name);
		
		std::string toString();
		
		SymbolTable() { }
		~SymbolTable();
};

#endif
