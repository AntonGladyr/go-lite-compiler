#ifndef FUNCDECL_CPP
#define FUNCDECL_CPP

#include <iostream> //delete
#include <string>
#include <sstream>
#include "AST/Declaration/FunctionDeclaration.hpp"
#include "Const/Constants/Constants.hpp"
#include "TypeDescriptorTable/TypeDescriptorTable.hpp"

void FunctionDeclaration::accept(Visitor& v) {
	v.visit(this);
}

std::string FunctionDeclaration::toString() {
	std::stringstream ss;

	//TODO: fix block output
	ss << "func " << idExp->name;
	ss << "(";
	
	//parameters	
	if (params) {
		for(auto const& param : *params) {
			ss << param->idExp->name << " ";
			
			if (param->typeName) {
				if (param->typeName->indexes) {
					for(auto const& index : *(param->typeName->indexes)) {
						ss << "[" << std::to_string(index) << "]";
					}
				}
				
				ss << param->typeName->name;
				if (&param != &params->back())
					ss << ", ";
			}
			
		}
	}
	
	ss << ") ";
	
	//function type
	//indexes	
	if (typeName) {
		if (typeName->indexes) {
			for(auto const& index : *(typeName->indexes)) {
				ss << "[" << std::to_string(index) << "]";
			}	
		}	
		//type name
		ss << typeName->name << " ";
	}

	return ss.str();
}

std::string FunctionDeclaration::symbolToStr() {
	std::stringstream ss;
	ss << idExp->name << " [" << CATEGORY_FUNC << "]" << " = ";
	ss << symbolSignatureToStr();
	return ss.str();
}

std::string FunctionDeclaration::symbolTypeToStr() {
	std::stringstream ss;
	
	if (typeName) {
		// array indexes
		if (typeName->indexes) {	
			for(auto const& index : *(typeName->indexes)) {
				ss << "[" << std::to_string(index) << "]";
			}	
		}	
		// type id
		ss << typeName->name;
	}
	else {
		ss << "void";
	}

	return ss.str();
}

std::string FunctionDeclaration::symbolSignatureToStr() {
	std::stringstream ss;
	
	if (idExp->name.compare(SPECIALFUNC_INIT) == 0)
		return "<unmapped>";
	
	// params
	ss << "(";
	if (params) {
		for(auto const& param : *params) {
			// for each id print type
			if (param->typeName->indexes) {
				for(auto const& index : *(param->typeName->indexes)) {
					ss << "[" << std::to_string(index) << "]";
				}	
			}
			
			ss << param->typeName->name;
			if (&param != &params->back())
				ss << ", ";
		}

	}
	ss << ")";
	
	ss << " -> ";

	ss << symbolTypeToStr();

	return ss.str();
}

std::string FunctionDeclaration::initCallToCcode(unsigned int initFuncNum) {
	std::stringstream ss;
	ss << "\t" << kPrefix << "init_" << initFuncNum << "();" << std::endl;
	return ss.str();
}

std::string FunctionDeclaration::mainCallToCCode() {
	std::stringstream ss;
	ss << "\t" << kPrefix << "main();" << std::endl;
	return ss.str();
}

std::string FunctionDeclaration::toCcode(unsigned int initFuncNum) {
	std::stringstream ss;
	
	if (idExp->name.compare(SPECIALFUNC_INIT) == 0)
		ss << C_VOID << " " << kPrefix << idExp->name
		   << "__" << initFuncNum;
	else if (idExp->type.baseType.compare(BASETYPE_STRING) == 0)
		ss << "const " << TypeDescriptorTable::getInstance().getTypeDescriptor(idExp->type.baseType)
		   << " " << kPrefix << idExp->name; 
	else if (idExp->type.isBaseType())
		ss << TypeDescriptorTable::getInstance().getTypeDescriptor(idExp->type.baseType)
	           << " " << kPrefix << idExp->name;
	else if (idExp->type.indexes) {
		ss << idExp->type.name << "* " << kPrefix << idExp->name; //TODO: multidemensional array
	}
	else	
		ss << idExp->type.name << " " << kPrefix << idExp->name;
	
	ss << "(";
	if (params) {
		for(auto const& param : *params) {
			// for each id print type	
			if (param->idExp->symbol)
				ss << TypeDescriptorTable::getInstance().getTypeDescriptor(
					param->idExp->symbol->baseType) << " ";
			else if (param->idExp->type.isBaseType())
				ss << TypeDescriptorTable::getInstance().getTypeDescriptor(
					param->idExp->type.baseType) << " "; // base type
			//TODO: multidemensional array
			/*else (param->idExp->type->indexes)
				ss << */
			/*else ss << TypeDescriptorTable::getInstance().getTypeDescriptor(
					param->idExp->type.name << " "); // derived type*/
			
			ss << param->idExp->name; // id

			if (param->typeName->indexes) {
				for(auto const& index : *(param->typeName->indexes)) {
					ss << "[" << std::to_string(index) << "]";
				}	
			}
				
			if (&param != &params->back())
				ss << ", ";
		}

	}
	ss << ") ";
	return ss.str();
}

FunctionDeclaration::~FunctionDeclaration() {
	delete idExp;

	if (params) {
		for(auto const& param : *params) {
			delete param;
		}
		delete params;
	}

	if (typeName) delete typeName;
	
	delete blockStmt;
	
	// for testing purposes
	// std::cout << "FunctionDeclaration destroyed" << std::endl;
}

#endif
