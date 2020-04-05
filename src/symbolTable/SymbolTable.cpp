#ifndef SYMBOLTABLE_CPP
#define SYMBOLTABLE_CPP

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "SymbolTable/SymbolTable.hpp"
#include "SymbolTable/HashFunction.h"
#include "AST/Declaration/FunctionDeclaration.hpp"

SymbolTable::SymbolTable(Program *prg) {
	SymbolTableBuilder builder;
	SymbolTable *sbPtr = builder.build(prg);
	std::copy(std::begin(sbPtr->table), std::end(sbPtr->table), std::begin(table));
	childList = sbPtr->childList;
	parent = sbPtr->parent;
	ss << sbPtr->ss.str();
}

void SymbolTable::build(Program *prg) {
	SymbolTableBuilder builder;
	SymbolTable *sbPtr = builder.build(prg);
	std::copy(std::begin(sbPtr->table), std::end(sbPtr->table), std::begin(table));	
	childList = sbPtr->childList;
	parent = sbPtr->parent;
	ss << sbPtr->ss.str();
}

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
	int i = Hash(name);	
	for (Symbol *s = this->table[i]; s; s = s->next) {
		// check if init function, so we allow to declare init function multiple times at the top-level scope
		if (isInitFunc(node)) break;
		
		// if id already declared, throw an error
		if (isEqual(s->name, name, s, node)) return NULL;	
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

bool SymbolTable::isInitFunc(Node *node) {
	if (node == NULL) return false;
	
	if (typeid(IdentifierExp) != typeid(*node)) return false;
	IdentifierExp *idExp = (IdentifierExp*)node;

	if (typeid(FunctionDeclaration) == typeid(*(idExp->parentNode))) {
		FunctionDeclaration *funcDecl = (FunctionDeclaration*)idExp->parentNode;	
		return (funcDecl->idExp->name.compare(SPECIALFUNC_INIT) == 0);
	}
}

bool SymbolTable::isEqual(
	const std::string &id,
	const std::string &newId,
	Symbol *s,
	Node *node
) {
	if (id.compare(newId) == 0) {
		std::cerr << ss.str();
		std::cerr << "Error:";
		if (node) std::cerr << " (line " <<  node->lineno << ")";
		std::cerr << " identifier " << id << " already declared on line "
			  << s->node->lineno << std::endl;
		return true;
	}
	
	return false;
}

std::string SymbolTable::toString() {	
	return ss.str(); 
}

void SymbolTable::deallocate() {
	// delete child and parent nodes		
	SymbolTable *current = this;
	
	// find the head of the tree (symboltable)
	while(current->parent != NULL) {
		if (current == parent) break;
		current = parent;	
	}
		
	// delete all childs
	for (auto &child : current->childList) {	
		if (child) {
			child->parent = NULL;
			child->deallocate();
		} else {
			delete child;
		}
	}	
}

SymbolTable::~SymbolTable() {
	// delete table	(scope)
	for (int i = 0; i < HashSize; i++) {	
		if (table[i]) {		
			delete table[i];
			table[i] = NULL;
		}
	}	
}

#endif
