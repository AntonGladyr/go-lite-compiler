#ifndef VARIABLEDECLARATION_HPP
#define VARIABLEDECLARATION_HPP

#include <vector>
#include <string>
#include "Services/Visitor.hpp"
#include "AST/Declaration/Declaration.hpp"
#include "AST/Expression/Expression.hpp"
#include "AST/Expression/IdentifierExp.hpp"
#include "AST/Declaration/TypeName.hpp"

class IdentifierExp;

class VariableDeclaration : public Declaration {
	public:		
		std::vector<IdentifierExp*> *idList = NULL;
		std::vector<Expression*> *expList = NULL;
		TypeName *typeName = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string symbolToStr() override ;
		virtual std::string symbolTypeToStr() override;
		virtual std::string toString();
		
		VariableDeclaration(
			std::vector<IdentifierExp*> *_idList,
			TypeName *_typeName,
			int _lineno
		) : idList(_idList), typeName(_typeName), Declaration(_lineno) { }

		VariableDeclaration(
			std::vector<IdentifierExp*> *_idList,
			std::vector<Expression*> *_expList,
			int _lineno
		);
		
		VariableDeclaration(
			std::vector<IdentifierExp*> *_idList,
			TypeName *_typeName,
			std::vector<Expression*> *_expList,
			int _lineno
		); 
		
		VariableDeclaration() { }
		~VariableDeclaration();	
};

#endif
