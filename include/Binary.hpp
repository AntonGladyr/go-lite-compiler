#ifndef BINARY_H
#define BINARY_H

#include <Expression.hpp>
#include <treeEnums.h>



    /**
     *
     *   +
     *   -
     *   *
     *   /
     *   %
     *   &
     *   |
     *   ^
     *   &^
     *   <<
     *   >>
     *   ==
     *   !=
     *   <
     *   >
     *   <=
     *   >=
     *   &&
     *   ||
     */
    class Binary : public Expression {
    public:


        Expression* left_operand_ = nullptr;
        Expression* right_operand_ = nullptr;
        BinaryKind kind_;

       

      
        Binary(Expression* lhs, Expression* rhs, BinaryKind kind) : left_operand_(lhs), right_operand_(rhs), kind_(kind) {}

        bool isBinary() { return true; }

     
        
    };

#endif
