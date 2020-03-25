#ifndef VARIABLEDECLARATION_HPP
#define VARIABLEDECLARATION_HPP

#include <vector>
#include <string>
#include "Visitor.hpp"
#include "Declaration.hpp"
#include "Expression.hpp"
#include "IdentifierExp.hpp"

class VariableDeclaration : public Declaration {
	public:		
		std::vector<IdentifierExp*> idList;
		std::vector<Expression*> expList;
		//std::string type;
		std::pair<std::string, std::vector<int>> type;
		
		virtual void accept(Visitor& v) override;
		
		/*VariableDeclaration(std::vector<IdentifierExp*> _idList,
				    const std::string &_type, int _lineno) :
			idList(_idList), type(_type), Declaration(_lineno) { }*/
		VariableDeclaration(std::vector<IdentifierExp*> _idList,
				    std::pair<std::string, std::vector<int>> _type,
				    int _lineno) :
			idList(_idList), type(_type), Declaration(_lineno) { }
		VariableDeclaration(std::vector<IdentifierExp*> _idList,
				    std::vector<Expression*> _expList) :
			idList(_idList), expList(_expList) { }
		/*VariableDeclaration(std::vector<IdentifierExp*> _idList,
				    const std::string &_type,
				    std::vector<Expression*> _expList) :
			idList(_idList), type(_type), expList(_expList) { }*/
		VariableDeclaration(std::vector<IdentifierExp*> _idList,
				    std::pair<std::string, std::vector<int>> _type,
				    std::vector<Expression*> _expList):
			 idList(_idList), type(_type), expList(_expList) { }
		VariableDeclaration() { }
		~VariableDeclaration();	
};

#endif
