 class UnaryExpression : public Expression {
    public:
        Expression* operand_ = nullptr;
        UnaryExpression(ExpressionKind kind, Expression* operand) : operand_(operand), kind_(kind) {}

 }