#ifndef INCDECSTATEMENT_HPP
#define INCDECSTATEMENT_HPP

#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Expression/Expression.hpp"

enum class INC_DEC_OP { INC, DEC };

class IncDecStatement : public Statement {	
	public:
		Expression *exp = NULL;
		INC_DEC_OP op;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
		
		IncDecStatement(
			Expression *_exp,
			INC_DEC_OP _op,
			int _lineno
		) : exp(_exp), op(_op), Statement(_lineno) { }

		IncDecStatement() { }
		~IncDecStatement();		
};

#endif
