 class UnaryExpression : public Expression {
    public:
        Expression* operand_ = nullptr;
        ExpressionKind kind_;
        UnaryExpression(ExpressionKind kind, Expression* operand) : operand_(operand), kind_(kind) {}

 }