#ifndef PRINTSTATEMENT_HPP
#define PRINTSTATEMENT_HPP

#include <vector>
#include "Services/Visitor.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Expression/Expression.hpp"

class PrintStatement : public Statement {
	public:
		std::vector<Expression*> *expList = NULL;
		bool isPrintln;	
		virtual void accept(Visitor& v) override;
		virtual std::string toString();
		
		PrintStatement(
			std::vector<Expression*> *expList,
			int _lineno	
		) : expList(expList), Statement(_lineno) { }

		PrintStatement(
			std::vector<Expression*> *expList,
			bool _isPrintln,
			int _lineno	
		) : expList(expList), isPrintln(_isPrintln), Statement(_lineno) { }


		PrintStatement() { }
		~PrintStatement();	
};

#endif
