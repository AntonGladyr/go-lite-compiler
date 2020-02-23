#include "Expression.hpp"

class ShortDeclaration : Declaration {
	public:
		std::string id;
		Expression exp;

		ShortDeclaration() { }
		ShortDeclaration(std::string id, Expression exp) : Declaration(k_declKindShortDec), id{id}, exp{exp};
}
