#ifndef INCDECSTATEMENT_HPP
#define INCDECSTATEMENT_HPP

#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Expression/Expression.hpp"

class IncDecStatement : public Statement {
	//std::string id;
	//Expression exp;

	public:
		virtual void accept(Visitor& v) override;
		
		IncDecStatement() { }
		~IncDecStatement();
		
		/*IncDecStatement(StatementKind kind, std::string id) : Statement(kind), id{id} { }
		IncDecStatement(StatementKind kind, std::string id, Expression exp) : Statement(kind), id{id}, exp{exp} { }*/
};

#endif
