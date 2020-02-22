class PrettyPrinter {
    public:
        PrettyPrinter(Instruction *rootIns) : this.rootIns{rootIns}

        void printProgram() {
            prettyInstruction(rootIns, 0);
        }

    private: 
        Instruction *rootIns;

        void prettyInstruction(Instruction *ins, int numTabs) {
            if(NULL == ins) {
                return;
            }

            printTabs(numTabs);
            switch(ins->kind) {
                case k_insKindDecl: prettyDeclaration(ins->val.decl); break; 
                case k_insKindStmt: prettyStatement(ins->val.stmt, numTabs); break;
                case k_insKindBlock: 
                    cout << "{" << endl;
                    prettyInstruction(ins->val.block, numTabs + 1); 
                    printTabs(numTabs);
                    cout << "}" << endl;
                    break;
            }

            prettyInstruction(ins->next, numTabs);
        } 

        void prettyDeclaration(Declaration *d) {
            switch(d->kind) {
                case k_declKindDeclare: 
                    cout << "var " << d->val.declareDecl.ids << " " << d->val.declareDecl.type << ";" << endl;
                    break;
                case k_declKindAssign: 
                    cout << "var " << d->val.assignDecl.ids << " = " << prettyExpression(d->val.assignDecl.rhs) << endl;
                    break;
                case k_declKindFactor: break;
                case k_declKindFunc: break;
                case k_declKindShortDec: break;
                case k_declKindType: break;
                case k_declKindTypeStruct: break;
            }
        }

        void prettyStatement(Statement *s, int numTabs) {

        }

        void prettyExpression(Expression *e, int numTabs) {

        }
}