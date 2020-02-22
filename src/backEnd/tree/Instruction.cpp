#include "Instruction.h"
#include "treeEnums.h"
#include "Declaration.h"
#include "Statement.hpp"

class Instruction {
    public:
        Instruction *next;
        InstructionKind kind;
        union val {
            Declaration decl;
            Statement stmt;
            Instruction block;
        };

        Instruction(Declaration _decl, Instruction *_next) 
            : kind{k_insKindDecl}, val.decl{_decl}, val.next{_next} {
        }

        Instruction(Statement _stmt, Instruction *_next) 
            : kind{k_insKindStmt} val.stmt{_stmt}, val.next{_next} {
        }

        Instruction(Instruction _ins, Instruction *_next) 
            : kind{k_insKindBlock}, val.block{_ins}, val.next{_next} {
        }

    private:
}