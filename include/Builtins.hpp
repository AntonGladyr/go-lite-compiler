#ifndef BUILTINS_H
#define BUILTINS_H

#include <Expression.hpp>


    class Builtins : public Expression {
    public:
	union val {
		Expression* left_expression_ ;
		Expression* right_expression_ ;
        };
	Expression* expression_;
	//append
        Builtsins(ExpressionKind kind, Expression* left_expression, Expression* right_expression);
	//cap and len
 	Builtsins(ExpressionKind kind, Expression* expression) ;

        bool isBuiltins();

      
   
       
    };

#endif
