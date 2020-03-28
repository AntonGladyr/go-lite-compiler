#ifndef VARIABLEDECLARATION_HPP
#define VARIABLEDECLARATION_HPP

#include <vector>
#include <string>
#include "Services/Visitor.hpp"
#include "AST/Declaration/Declaration.hpp"
#include "AST/Expression/Expression.hpp"
#include "AST/Expression/IdentifierExp.hpp"

class IdentifierExp;

class VariableDeclaration : public Declaration {
	public:		
		std::vector<IdentifierExp*> *idList;
		std::vector<Expression*> *expList;
		std::pair<std::string, std::vector<int>*> *type;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();
		
		VariableDeclaration(
			std::vector<IdentifierExp*> *_idList,
			std::pair<std::string, std::vector<int>*> *_type,
			int _lineno
		) : idList(_idList), type(_type), Declaration(_lineno) { }

		VariableDeclaration(
			std::vector<IdentifierExp*> *_idList,
			std::vector<Expression*> *_expList,
			int _lineno
		) : idList(_idList), expList(_expList), Declaration(_lineno) { }
		
		VariableDeclaration(
			std::vector<IdentifierExp*> *_idList,
			std::pair<std::string, std::vector<int>*> *_type,
			std::vector<Expression*> *_expList,
			int _lineno
		) : idList(_idList), type(_type), expList(_expList), Declaration(_lineno) { }
		
		VariableDeclaration() { }
		~VariableDeclaration();	
};

#endif
