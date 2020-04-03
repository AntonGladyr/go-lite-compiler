#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <string>
#include <sstream>
#include "SymbolTable/Symbol.hpp"
#include "SymbolTable/HashFunction.h"
#include "AST/Node.hpp"

const std::string BASETYPE_UNDEFINED =  "<infer>";
const std::string BASETYPE_INT = "int";
const std::string BASETYPE_FLOAT = "float64";
const std::string BASETYPE_RUNE = "rune";
const std::string BASETYPE_STRING = "string";
const std::string BASETYPE_BOOL = "bool";
const std::string CONSTANT_TRUE = "true";
const std::string CONSTANT_FALSE = "false";
const std::string CATEGORY_TYPE = "type";
const std::string CATEGORY_CONST = "constant";
const std::string CATEGORY_VAR = "variable";
const std::string CATEGORY_FUNC = "function";
const std::string SPECIALFUNC_MAIN = "main";
const std::string SPECIALFUNC_INIT = "init";

class Symbol {
	public:
		std::string name;
		std::string category;
		std::string type;
		Symbol *next = NULL;
		Node *node = NULL;
		
		std::string toString();
		
		Symbol(
			const std::string &_name,
			const std::string &_category,
			const std::string &_type,
			Symbol *_next,
			Node *_node
		) : name(_name), category(_category), type(_type), next(_next), node(_node) { }

		Symbol() { }
		~Symbol();
};

#endif
