 class Literal: public Expression{
    public : 
    bool value_;
    int line_;
    Literal(bool value, int line) : value_(value), line_(line){}

 }