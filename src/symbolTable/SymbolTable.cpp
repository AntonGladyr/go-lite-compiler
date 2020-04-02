#ifndef SYMBOLTABLE_CPP
#define SYMBOLTABLE_CPP

#include <iostream>
#include <sstream>
#include <vector>
#include "SymbolTable/SymbolTable.hpp"
#include "SymbolTable/HashFunction.h"
#include "AST/Declaration/FunctionDeclaration.hpp"

SymbolTable *SymbolTable::scopeSymbolTable() {
	SymbolTable *t = new SymbolTable();
	t->parent = this;	
	// copy pointer to the child for memory deallocation
	this->childList.push_back(t);
	return t;
}

SymbolTable *SymbolTable::unscopeSymbolTable() {
	if (this->parent) {	
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
	FunctionDeclaration *funcDecl = NULL;
	if (node != NULL) {
		if (typeid(FunctionDeclaration) == typeid(*node))
			funcDecl = (FunctionDeclaration*)node;
	}

	int i = Hash(name);	
	for (Symbol *s = this->table[i]; s; s = s->next) {
		// check if init function, so we allow to declare init function multiple times at the top-level scope
		if(funcDecl) {	
			if(funcDecl->id.compare(SPECIALFUNC_INIT) == 0) break;
		}
		
		if (s->name.compare(name) == 0) {
			std::cerr << ss.str();
			std::cerr << "Error:";
			if (node) std::cerr << " (line " <<  node->lineno << ")";
			std::cerr << " identifier " << name << " already declared on line "
				  << s->node->lineno << std::endl;
			return NULL;
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
	//TODO: fix for parent nodes
	
	/*for (auto &child : childList) {
		if (child) {
			child->parent = NULL;	
			delete child;
			child = NULL;	
		}
	}*/
		
	/*for (int i = 0; i < HashSize; i++) {
		if (table[i]) { 
			delete table[i];
			table[i] = NULL;
		}
	}*/
}

#endif
