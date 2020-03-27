#ifndef EMPTYSTMT_HPP
#define EMPTYSTMT_HPP

#include <vector>
#include "Services/Visitor.hpp"

class EmptyStatement : public Statement {
	public:	
		virtual void accept(Visitor& v) override;
		virtual std::string toString() { }

		EmptyStatement(	
			int _lineno
		) : Statement(_lineno) { }
		
		EmptyStatement() { }
		~EmptyStatement();
};

#endif
