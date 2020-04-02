#ifndef IDENTIFIEREXP_HPP
#define IDENTIFIEREXP_HPP

#include <string>
#include "Services/Visitor.hpp"
#include <AST/Expression/Expression.hpp>
#include "AST/Node.hpp"

class IdentifierExp : public Expression {
	public:
		std::string id;
		Symbol *symbol = NULL;
		Node *parentNode = NULL;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
	
		IdentifierExp(
			const std::string &_id,
			int _lineno
		) : id(_id), Expression(_lineno) { }
		
		IdentifierExp() { }
		~IdentifierExp();
};

#endif
