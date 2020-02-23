#ifndef LITERAL_H
#define LITERAL_H

#include <Expression.hpp>
#include <sstream>
#include <regex>


    class Literal : public Expression {
        public::
        bool valueBool;
	int valueInt;
	float valueFloat;
	char* valueChar; 
	char* identifier;
	bool f_rune_ = false;
        bool f_raw_ = false;

	//boolean
        Literal(ExpressionKind kind, bool value) :kind_(kind), valueBool(value);
	//float
 	Literal(ExpressionKind, float value) : kind_(kind), valueFloat(value);
	//rune And string
	 Literal(ExpressionKind kind, char* value) : kind_(kind), valueChar(value);
	//integer
         Literal(ExpressionKind kind, int value) : kind_(kind), valueInt(value);

	bool isLiteral() { return true; }
    };


   

#endif
