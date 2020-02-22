#ifndef GOLITE_EXPRESSIONS_UNARY_H
#define GOLITE_EXPRESSIONS_UNARY_H

#include <Expression.hpp>



    /**
     * Class representing unary expression
     * unary_expression: <operator> <expr>
     * operator:
     *     -
     *     !
     *     +
     *     ^
     */
    class Unary : public Expression {
    public:

	Expression* operand_ = nullptr;
        UnaryKind kind_;
       
       
        Unary(Expression* operand, UnaryKind kind) : operand_(operand), kind_(kind) {}


        int getLine();

       
        bool isUnary() { return true; }

      
    };


#endif
