#ifndef TYPEDECLARATION_HPP
#define TYPEDECLARATION_HPP

#include <string>
#include "Services/Visitor.hpp"
#include "AST/Declaration/Declaration.hpp"

class TypeDeclaration : public Declaration {
	public:
		std::string newType;
		std::string existingType;
		
		virtual void accept(Visitor& v) override;

		TypeDeclaration() { }
		~TypeDeclaration();
		/*TypeDeclaration(std::string newType, std::string existingType)
			: Declaration(k_declKindType), newType{newType}, existingType{existingType};*/
};

#endif
