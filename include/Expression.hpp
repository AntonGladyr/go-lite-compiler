#ifndef EXPRESSIONS_EXPRESSION_H
#define EXPRESSIONS_EXPRESSION_H

#include <string>


    class Expression {
    public:

        virtual bool isParenthesis() { return false; }
        virtual bool isIdentifier() { return false; }
        virtual bool isLiterals() { return false; }
        virtual bool isUnary() { return false; }
       
        virtual bool isBinary() { return false; }
        virtual bool isIndexing() { return false; }

        virtual bool isFieldSelectors() { return false; }
        virtual bool isBuiltins() { return false; }
	

      

      


       
        virtual int getLine() = 0;

       
    };

#endif

