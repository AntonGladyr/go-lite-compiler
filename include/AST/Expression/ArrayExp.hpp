#ifndef ARRAYEXP_HPP
#define ARRAYEXP_HPP

#include <vector>
#include <string>
#include "Services/Visitor.hpp"
#include "AST/Expression/Expression.hpp"


class ArrayExp : public Expression {
	public:	
		IdentifierExp *idExp = NULL;
		std::vector<Expression*> *expList = NULL;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
			
		ArrayExp(
			IdentifierExp *_idExp,
			std::vector<Expression*> *_expList,
			int _lineno
		) :idExp(_idExp), expList(_expList), Expression(_lineno) { }
		
		ArrayExp() { }
		~ArrayExp();	
};

#endif
