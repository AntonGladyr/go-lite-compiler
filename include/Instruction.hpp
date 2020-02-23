#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include "tree.h"

class Instruction {
    public:
        Instruction *next;
        union {
            Declaration *decl;
            Statement *stmt;
            Instruction *block;
        } val;

        Instruction(Declaration *_decl, Instruction *_next); 
        Instruction(Statement *_stmt, Instruction *_next);
        Instruction(Instruction *_ins, Instruction *_next);

};

#endif
