#ifndef FUNCTIONDECLARATION_HPP
#define FUNCTIONDECLARATION_HPP

#include <vector>
#include <string>
#include "Services/Visitor.hpp"
#include "AST/Declaration/Declaration.hpp"

class FunctionDeclaration : public Declaration {
	public:
		std::string id;
		std::vector<std::string> locals;
		std::string type;

		virtual void accept(Visitor& v) override;

		FunctionDeclaration() { }
		~FunctionDeclaration();
		/*FunctionDeclaration(string id, vector<std::string> locals, string type, Instruction *body)
			: Declaration(k_declKindFunc), locals{locals}, type{type}, body{body};*/
};

#endif
