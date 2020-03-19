#include <vector>
#include <string>
#include "Declaration.hpp"
#include "Visitor.hpp"

class VariableDeclaration : public Declaration {
	public:		
		std::vector<std::string> idList;
		std::string type;
		virtual void accept(Visitor& v) override;

		
		VariableDeclaration() { }
		~VariableDeclaration();	
		VariableDeclaration(std::vector<std::string> _idList, const std::string &_type, int _lineno) :
			idList(_idList), type(_type), Declaration(_lineno) { }
};
