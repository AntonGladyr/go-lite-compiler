#ifndef FUNCTIONPARAMETER_HPP
#define FUNCTIONPARAMETER_HPP

#include "AST/Expression/IdentifierExp.hpp"
#include "AST/Declaration/TypeName.hpp"

class FunctionParameter { 
	public:
		IdentifierExp *idExp = NULL;
		TypeName *typeName = NULL;
		int lineno;
			
		FunctionParameter(
			IdentifierExp *_idExp,
			TypeName *_typeName,	
			int _lineno
		) : idExp(_idExp), typeName{_typeName}, lineno(_lineno) { }
	
		FunctionParameter() { }
		~FunctionParameter();
};

#endif
