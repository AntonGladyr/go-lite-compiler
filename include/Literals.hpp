#ifndef LITERALS_H
#define LITERALS_H

#include <Expression.hpp>
#include <sstream>
#include <regex>

    template <class T>
    class Literal : public Expression {};

    template <>
    class Literal<bool> : public Expression {
        public:
        bool value_;
        int line_;

        Literal(bool value, int line) : value_(value), line_(line){}
        
        bool isLiteral() { return true; }
    };

    template <>
    class Literal<int> : public Expression {
    public:
        int value_;
        int line_;

        Literal(int value, int line) : value_(value), line_(line){}
       
        bool isLiteral() { return true; }
       
    };

    template <>
    class Literal<char*> : public Expression {
        public:
        char* value_;
        int line_;

        bool f_rune_ = false;
        bool f_raw_ = false;
        Literal(char* value, int line) : value_(value), line_(line){}
        
        
        bool isLiteral() { return true; }
       
    };

    template <>
    class Literal<float> : public Expression {
    public:
        float value_;
        int line_;
        Literal(float value, int line) : value_(value), line_(line){}
        
        bool isLiteral() { return true; }
       
    };

#endif
