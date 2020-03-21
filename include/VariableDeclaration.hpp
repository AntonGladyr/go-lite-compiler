#include <vector>
#include <string>
#include "Visitor.hpp"
#include "Declaration.hpp"
#include "Expression.hpp"

class VariableDeclaration : public Declaration {
	public:		
		std::vector<std::string> idList;
		std::vector<Expression*> expList;
		std::string type;

		virtual void accept(Visitor& v) override;
		
		VariableDeclaration() { }
		~VariableDeclaration();	
		VariableDeclaration(std::vector<std::string> _idList,
				    const std::string &_type, int _lineno) :
			idList(_idList), type(_type), Declaration(_lineno) { }
		VariableDeclaration(std::vector<std::string> _idList,
				    std::vector<Expression*> _expList) :
			idList(_idList), expList(_expList) { }
		VariableDeclaration(std::vector<std::string> _idList,
				    const std::string &_type,
				    std::vector<Expression*> _expList) :
			idList(_idList), type(_type), expList(_expList) { }
};