#ifndef TYPEDECLARATION_HPP
#define TYPEDECLARATION_HPP

#include <string>
//#include "Node.hpp"
#include "Declaration.hpp"

class TypeDeclaration : public Declaration { // : public Node { , 
	public:
		std::string newType;
		std::string existingType;

		TypeDeclaration() { }
		/*TypeDeclaration(std::string newType, std::string existingType)
			: Declaration(k_declKindType), newType{newType}, existingType{existingType};*/
};

#endif
