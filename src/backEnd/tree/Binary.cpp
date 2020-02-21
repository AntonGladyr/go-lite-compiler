
class Binary: public Expression {
    public : 
    // expression + ...
    Expression* left_operand_ = nullptr;

    // ... + expression
    Expression* right_operand_ = nullptr;
    Binary(Expression* lhs, Expression* rhs, ExpressionKind kind) : left_operand_(lhs), right_operand_(rhs), kind_(kind) {}


}