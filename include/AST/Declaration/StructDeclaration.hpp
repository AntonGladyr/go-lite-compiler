#include <vector>

class StructDeclaration : Declaration {
	public:
		std::string id;
		std::vector<std::vector<std::string>> structdecl_list;

		StructDeclaration() { }
		StructDeclaration() : Declaration(k_declKindTypeStruct), structdecl_list{structdecl_list};
}
