#ifndef FUNCTIONDECLARATION_HPP
#define FUNCTIONDECLARATION_HPP

#include <vector>
#include <string>
#include <utility>
#include "Services/Visitor.hpp"
#include "AST/Declaration/Declaration.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Statement/BlockStatement.hpp"
#include "AST/Expression/IdentifierExp.hpp"
#include "AST/Declaration/TypeName.hpp"
#include "AST/Declaration/FunctionParameter.hpp"
#include "TypeDescriptor/TypeDescriptor.hpp"

class BlockStatement;
class IdentifierExp;
class FunctionParameter;

class FunctionDeclaration : public Declaration {
	public:
		IdentifierExp *idExp = NULL;
		std::vector<FunctionParameter*> *params = NULL;
		TypeName *typeName = NULL;
		BlockStatement *blockStmt = NULL;
		
		TypeName getType() { return *typeName; }
		std::string symbolSignatureToStr();
		std::string mainCallToCCode();	
		std::string initCallToCcode(unsigned int initFuncNum);
		std::string toCcode(unsigned int initFuncNum);
		virtual void accept(Visitor& v) override;
		virtual std::string symbolToStr() override ;
		virtual std::string symbolTypeToStr() override;
		virtual std::string toString();
		
		FunctionDeclaration(
			IdentifierExp *_idExp,
			std::vector<FunctionParameter*> *_params,
			BlockStatement *_blockStmt,
			int _lineno
		) : idExp(_idExp), 
		    params{_params},
		    blockStmt{_blockStmt},
		    Declaration(_lineno) { };
		
		FunctionDeclaration(
			IdentifierExp *_idExp,
			std::vector<FunctionParameter*> *_params,
			TypeName *_typeName,
			BlockStatement *_blockStmt,
			int _lineno
		) : idExp(_idExp), 
		    params{_params},
		    typeName(_typeName),
		    blockStmt{_blockStmt},
		    Declaration(_lineno) { };
		
		FunctionDeclaration() { }
		~FunctionDeclaration();
};

#endif
