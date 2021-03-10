#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <sstream>
#include "SymbolTable/Symbol.hpp"
#include "SymbolTable/HashFunction.h"
#include "AST/Node.hpp"


class Symbol {
	public:
		std::string name;
		std::string category;
		std::string type;
		std::string baseType;
		Symbol *symbType = NULL;
		int tmpCounterNum;	
		Symbol *next = NULL;
		Node *node = NULL;
		
		std::string toString();
		
		Symbol(
			const std::string &_name,
			const std::string &_category,
			const std::string &_type,
			const std::string &_baseType,
			Symbol *_next,
			Node *_node
		) : name(_name), category(_category), type(_type), baseType(_baseType), next(_next), node(_node) { }

		Symbol() { }
		~Symbol();
};

#endif
