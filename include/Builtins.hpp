#ifndef BUILTINS_H
#define BUILTINS_H

#include <Expression.hpp>


    class Builtins : public Expression {
    public:
	Expression* left_expression_ = nullptr;
        Expression* right_expression_ = nullptr;
        Builtsins(Expression* left_expression, Expression* right_expression) :
                left_expression_(left_expression), right_expression_(right_expression){}

        bool isBuiltins() { return true; }

      
   
       
    };

#endif
