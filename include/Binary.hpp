#ifndef BINARY_H
#define BINARY_H

#include <Expression.hpp>
#include <treeEnums.h>


    class Binary : public Expression {
    public:

	
        Expression* left_operand_ = nullptr;
        Expression* right_operand_ = nullptr;

       

      
        Binary( ExpressionKind kind, Expression* lhs, Expression* rhs);
        bool isBinary() ;

     
        
    };

#endif
