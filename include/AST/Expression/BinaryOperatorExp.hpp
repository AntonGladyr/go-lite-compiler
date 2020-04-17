#ifndef BINARYOPERATOREXP_HPP
#define BINARYOPERATOREXP_HPP

#include <string>
#include <set>
#include "Services/Visitor.hpp"
#include "AST/Expression/Expression.hpp"

const std::string BINARY_PLUS 	= "+";
const std::string BINARY_MINUS 	= "-";
const std::string BINARY_TIMES	= "*";
const std::string BINARY_DIV 	= "/";
const std::string BINARY_REMAIN = "%";
const std::string BINARY_BWAND 	= "&";
const std::string BINARY_BWOR 	= "|";
const std::string BINARY_BWXOR 	= "^";
const std::string BINARY_LEFTSHIFT  = "<<";
const std::string BINARY_RIGHTSHIFT = ">>";
const std::string BINARY_BWANDNOT   = "&^";
const std::string BINARY_AND 	 = "&&";
const std::string BINARY_OR 	 = "||";
const std::string BINARY_EQUAL   = "==";
const std::string BINARY_NOTEQ   = "!=";
const std::string BINARY_GREATER =  ">";
const std::string BINARY_LESS  	 =  "<";
const std::string BINARY_GREATEREQ = ">=";
const std::string BINARY_LESSEQ    = "<=";

const std::set<std::string> integerOpList = {
	BINARY_REMAIN, BINARY_BWOR, BINARY_BWAND, BINARY_LEFTSHIFT, BINARY_RIGHTSHIFT, BINARY_BWANDNOT, BINARY_BWXOR
};

const std::set<std::string> numericOpList = { BINARY_PLUS, BINARY_MINUS, BINARY_TIMES, BINARY_DIV };

const std::set<std::string> orderedOpList = { BINARY_LESS, BINARY_GREATER, BINARY_GREATEREQ, BINARY_LESSEQ };

const std::set<std::string> boolOpList = { BINARY_OR, BINARY_AND };

const std::set<std::string> comparableOpList = { BINARY_EQUAL, BINARY_NOTEQ };


class BinaryOperatorExp : public Expression {
	public:
		std::string op;
		Expression *lhs = NULL;
		Expression *rhs = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();
		
		BinaryOperatorExp(
			const std::string &_op, 
			Expression *_lhs,
			Expression *_rhs,
			int _lineno
		) : op(_op), lhs(_lhs), rhs(_rhs), Expression(_lineno) { }	
		BinaryOperatorExp() { }
		~BinaryOperatorExp();
};

#endif
