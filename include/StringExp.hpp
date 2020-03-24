#ifndef STRINGEXP_HPP
#define STRINGEXP_HPP

#include <string>
#include "Visitor.hpp"
#include "Expression.hpp"

class StringExp : public Expression {
	public:
		std::string value;	

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
	
		StringExp(const std::string &_stringValue, int _lineno);
		StringExp() { }
		~StringExp();
	private:
		void findAndReplaceAll(std::string &data, std::string toSearch, std::string replaceStr);
};

#endif
