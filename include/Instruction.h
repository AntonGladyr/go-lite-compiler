class Instruction {
    public:
        Instruction next;
        InstructionKind kind;
        union val {
            Declaration decl;
            Statement stmt;
            Instruction block;
        };

        Instruction(Declaration _decl, Instruction _next);
        Instruction(Statement _stmt, Instruction _next);
        Instruction(Instruction _ins, Instruction _next);

    private:
}