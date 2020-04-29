#ifndef TYPE_DESCRIPTOR_HPP
#define TYPE_DESCRIPTOR_HPP

#include <set>
#include <string>
#include <vector>
#include "SymbolTable/Symbol.hpp"
#include "AST/Node.hpp"

const std::string BASETYPE_UNDEFINED = "<infer>";
const std::string BASETYPE_INT 	     = "int";
const std::string BASETYPE_FLOAT     = "float64";
const std::string BASETYPE_RUNE      = "rune";
const std::string BASETYPE_STRING    = "string";
const std::string BASETYPE_BOOL      = "bool";
const std::string CONSTANT_TRUE      = "true";
const std::string CONSTANT_FALSE     = "false";
const std::string CATEGORY_TYPE      = "type";
const std::string CATEGORY_CONST     = "constant";
const std::string CATEGORY_VAR       = "variable";
const std::string CATEGORY_FUNC      = "function";
const std::string SPECIALFUNC_MAIN   = "main";
const std::string SPECIALFUNC_INIT   = "init";


const std::set<std::string> orderedTypesList = { BASETYPE_INT, BASETYPE_FLOAT, BASETYPE_STRING, BASETYPE_RUNE };

const std::set<std::string> numericTypesList = { BASETYPE_INT, BASETYPE_FLOAT, BASETYPE_RUNE };

const std::set<std::string> integerTypesList = { BASETYPE_INT, BASETYPE_RUNE };

const std::set<std::string> 
baseTypesList = { BASETYPE_INT, BASETYPE_FLOAT, BASETYPE_BOOL, BASETYPE_STRING, BASETYPE_RUNE };


class TypeDescriptor {
	public:
		std::string name;	 // type name (base and derived types)
		std::string category;	 // there are 4 basic categories: type, constant, variable, function		
		std::string baseType;    // there are 5 base types: bool, int, float64, rune, string
		std::vector<int> *indexes = NULL; // array indexes
		Symbol *symbol = NULL;	 // pointer to the symbol table
		Node *node = NULL;	 // pointer to node in the AST

		// there are 6 type groups: bool, comparable, ordered, numeric, string, integer
		// the next functions help to identify a group type of the current type descriptor
		bool isOrderedType();
		bool isNumericType();
		bool isIntegerType();
		bool isStringType();
		bool isBoolType();
		bool isBaseType();
		bool isArray();
		static std::string resolveNumericType(
			const std::string &lhsType, 
			const std::string &rhsType
		);

		TypeDescriptor(
			const std::string &_name,
			const std::string &_baseType,
			const std::string &_category,
			std::vector<int> *_indexes,
			Node *_node	
		) : name(_name), baseType(_baseType), category(_category), indexes(_indexes), node(_node) { }

		TypeDescriptor(
			const std::string &_name,
			const std::string &_baseType,
			const std::string &_category,
			Node *_node	
		) : name(_name), baseType(_baseType), category(_category), node(_node) { }

		TypeDescriptor() { }
};

#endif
