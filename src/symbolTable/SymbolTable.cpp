#ifndef SYMBOLTABLE_CPP
#define SYMBOLTABLE_CPP

#include <iostream>
#include <sstream>
#include <vector>
#include "SymbolTable/SymbolTable.hpp"
//#include "../helpers/HashFunction.cpp"
#include "SymbolTable/HashFunction.h"

SymbolTable *SymbolTable::scopeSymbolTable() {
	SymbolTable *t = new SymbolTable();
	t->parent = this;
	t->headParent = headParent;
	// copy pointer to the child for memory deallocation
	this->childList.push_back(t);
	// copy a string stream for a symbol table printer
	//t->ss = this->ss;
	return t;
}

SymbolTable *SymbolTable::unscopeSymbolTable() {
	if (this->parent) {
		// copy a string stream for a symbol table printer
		//this->parent->ss = this->ss;
		return this->parent;
	}
	return NULL;
}

Symbol *SymbolTable::putSymbol(
	const std::string &name,
	const std::string &category,
	const std::string &type,
	Node *node
) {
	int i = Hash(name);	
	for (Symbol *s = this->table[i]; s; s = s->next) {
		if (s->name.compare(name) == 0) {
			std::cerr << "Error:";
			if (node) std::cerr << " (line " <<  node->lineno << ")";
			std::cerr << " identifier" << name << "already declared" << std::endl;
			exit(1);
		}
	}
	this->table[i] = new Symbol(name, category, type, this->table[i], node);
	return this->table[i];
}

Symbol *SymbolTable::getSymbol(SymbolTable *t, const std::string &name) {
	int i = Hash(name);

	 // Check the current scope
	for (Symbol *s = t->table[i]; s; s = s->next) {	
		if (s->name.compare(name) == 0) return s;
	}

	// Check for existence of a parent scope
	if (t->parent == NULL)
		return NULL;
	
	// Check the parent scopes
	return getSymbol(t->parent, name);
}


std::string SymbolTable::toString() {	
	return ss.str(); 
}

SymbolTable::~SymbolTable() {
	//TODO: fix memory deallocation
	/*for (auto &child : headParent->childList) {
		if (child) {	
			for (int i = 0; i < HashSize; i++) {
				if (table[i]) { 
					delete table[i];
					table[i] = NULL;
				}
			}
			delete child;
			child = NULL;
		}
	}*/
}

#endif
