#include <vector>
#include "Instruction.hpp"

class FunctionDeclaration : Declaration {
	public:
		std::string id;
		std::vector<string> locals;
		std::string type;
		Instruction *body;

	FunctionDeclaration() { }
	FunctionDeclaration(string id, vector<string> locals, string type, Instruction *body)
		: Declaration(k_declKindFunc), locals{locals}, type{type}, body{body};
}
