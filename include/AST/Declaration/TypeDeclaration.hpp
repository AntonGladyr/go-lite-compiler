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
		TypeName *type = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string symbolToStr() override ;
		virtual std::string symbolTypeToStr() override;
		virtual std::string toString();

		TypeDeclaration(
			IdentifierExp *_idExp,
			TypeName *_type,
			int _lineno
		) : idExp(_idExp), 
		    type(_type),
		    Declaration(_lineno) { }
		
		TypeDeclaration() { }
		~TypeDeclaration();
};

#endif
