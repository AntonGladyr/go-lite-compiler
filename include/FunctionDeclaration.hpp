#include <vector>
#include <string>

#include "Declaration.hpp"

class FunctionDeclaration : public Declaration {
	public:
		std::string id;
		std::vector<std::string> locals;
		std::string type;	

	FunctionDeclaration() { }
	/*FunctionDeclaration(string id, vector<std::string> locals, string type, Instruction *body)
		: Declaration(k_declKindFunc), locals{locals}, type{type}, body{body};*/
};
