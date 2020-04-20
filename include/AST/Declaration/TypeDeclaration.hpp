#ifndef TYPEDECLARATION_HPP
#define TYPEDECLARATION_HPP

#include <utility>
#include <string>
#include "Services/Visitor.hpp"
#include "AST/Declaration/Declaration.hpp"
#include "AST/Expression/IdentifierExp.hpp"
#include "AST/Declaration/TypeName.hpp"

class IdentifierExp;

class TypeDeclaration : public Declaration {
	public:
		IdentifierExp *idExp = NULL;
		TypeName *typeName = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string symbolToStr() override ;
		virtual std::string symbolTypeToStr() override;
		virtual std::string toString();

		TypeDeclaration(
			IdentifierExp *_idExp,
			TypeName *_typeName,
			int _lineno
		) : idExp(_idExp), 
		    typeName(_typeName),
		    Declaration(_lineno) { }
		
		TypeDeclaration() { }
		~TypeDeclaration();
};

#endif
