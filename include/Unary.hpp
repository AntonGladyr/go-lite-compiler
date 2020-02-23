#ifndef GOLITE_EXPRESSIONS_UNARY_H
#define GOLITE_EXPRESSIONS_UNARY_H

#include <Expression.hpp>

    class Unary : public Expression {
    public:

	Expression* operand_ = nullptr;
       
       
        Unary(Expression* operand, ExpressionKind kind);


        int getLine();

       
        bool isUnary();

      
    };


#endif
