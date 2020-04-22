#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <string>
#include <sstream>
#include <vector>
#include "SymbolTable/Symbol.hpp"
#include "SymbolTable/HashFunction.h"
#include "AST/Node.hpp"
#include "AST/Program/Program.hpp"
#include "Services/SymbolTableBuilder.hpp"

class SymbolTable {
	private:
		bool isInitFunc(Node *node);
		bool isEqual(const std::string &id, const std::string &newId, Symbol *s, Node *node);
		bool isSymbolMode = false;
	public:
		Symbol *table[HashSize] = {};
		SymbolTable *parent = NULL;	
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
		std::string findBaseType(SymbolTable *t, std::string type);
		void build(Program *prg); // build symbol table
		void deallocate(); //for memory deallocation
		
		std::string toString();
		
		SymbolTable(Program *prg);
		SymbolTable(Program *prg, bool _isSymbolMode); // for symbol table mode
		SymbolTable() { };
		~SymbolTable();
};

#endif
