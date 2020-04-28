#ifndef FUNCTIONCALLEXP_HPP
#define FUNCTIONCALLEXP_HPP

#include <vector>
#include <string>
#include "Services/Visitor.hpp"
#include "AST/Expression/Expression.hpp"


class FunctionCallExp : public Expression {
	public:	
		IdentifierExp *idExp = NULL;
		Expression *_identifierExp = NULL;  // for idExp
		std::vector<Expression*> *expList = NULL;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
			
		FunctionCallExp(
			Expression *_idExp,
			std::vector<Expression*> *_expList,
			int _lineno
		) : _identifierExp(_idExp), expList(_expList), Expression(_lineno) { }
		
		FunctionCallExp() { }
		~FunctionCallExp();	
};

#endif
