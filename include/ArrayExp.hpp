#ifndef ARRAYEXP_HPP
#define ARRAYEXP_HPP

#include <vector>
#include <string>
#include "Visitor.hpp"
#include "Expression.hpp"


class ArrayExp : public Expression {
	public:	
		std::string id;
		std::vector<Expression*> expList;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
			
		ArrayExp(const std::string &_id, std::vector<Expression*> _expList, int _lineno) :
			id(_id), expList(_expList), Expression(_lineno) { }
		ArrayExp() { }
		~ArrayExp();	
};

#endif
