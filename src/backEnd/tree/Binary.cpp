
class Binary: public Expression {
    public : 
    ExpressionKind kind;
    // expression + ...
    Expression* left_operand_ = nullptr;

    // ... + expression
    Expression* right_operand_ = nullptr;
    Binary(Expression* lhs, Expression* rhs, KIND kind) : left_operand_(lhs), right_operand_(rhs), kind_(kind) {
        
    }


}