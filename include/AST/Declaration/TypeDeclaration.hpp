#ifndef TYPEDECLARATION_HPP
#define TYPEDECLARATION_HPP

#include <utility>
#include <string>
#include "Services/Visitor.hpp"
#include "AST/Declaration/Declaration.hpp"

class TypeDeclaration : public Declaration {
	public:
		std::string id;
		std::pair<std::string, std::vector<int>*> *type = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();

		TypeDeclaration(
			std::string _id,
			std::pair<std::string, std::vector<int>*> *_type,
			int _lineno
		) : id(_id), type(_type), Declaration(_lineno) { }
		
		TypeDeclaration() { }
		~TypeDeclaration();
};

#endif
