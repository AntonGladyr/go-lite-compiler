#ifndef FUNCTIONPARAMETER_HPP
#define FUNCTIONPARAMETER_HPP

#include "AST/Expression/IdentifierExp.hpp"
#include "AST/Declaration/TypeName.hpp"

class FunctionParameter { 
	public:
		IdentifierExp *idExp = NULL;
		TypeName *type = NULL;
		int lineno;
			
		FunctionParameter(
			IdentifierExp *_idExp,
			TypeName *_type,	
			int _lineno
		) : idExp(_idExp), type{_type}, lineno(_lineno) { }
	
		FunctionParameter() { }
		~FunctionParameter();
};

#endif
