    class Binary : public Expression {
    public:

	
        Expression* left_operand_ = nullptr;
        Expression* right_operand_ = nullptr;

       

      
        Binary( ExpressionKind kind, Expression* lhs, Expression* rhs) : left_operand_(lhs), right_operand_(rhs), kind_(kind) {}

        bool isBinary() { return true; }

     
        
    };



