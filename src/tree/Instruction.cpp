class Instruction {
    public:
        Instruction *next;
        union val {
            Declaration *decl;
            Statement *stmt;
            Instruction *block;
        };

        Instruction(Declaration *_decl, Instruction *_next) : val.decl{_decl}, val.next{_next} {
        }

        Instruction(Statement *_stmt, Instruction *_next) : val.stmt{_stmt}, val.next{_next} {
        }

        Instruction(Instruction *_ins, Instruction *_next) : val.block{_ins}, val.next{_next} {
        }

    private:
}