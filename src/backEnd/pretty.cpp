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

        void prettyDeclaration(Declaration *d, int numTabs) {
            printTabs(numTabs);
            switch(d->kind) {
                case k_declKindDeclare: 
                    cout << "var " << d->val.declareDecl.ids << " " << d->val.declareDecl.type << ";" << endl;
                    break;
                case k_declKindAssign: 
                    cout << "var " << d->val.assignDecl.ids << " = " << prettyExpression(d->val.assignDecl.rhs, 0) << endl;
                    break;
                case k_declKindFactor: 
                    for(const auto& decl : d->val.factorDecl.decls) {
                        prettyDeclaration(d, numTabs);
                    }
                    break;
                case k_declKindFunc: 
                    cout << "func " << d->val.funcDecl.id << "(" << d->val.funcDecl.locals << ")" << d->val.funcDecl.type << "{" << endl;
                    prettyInstruction(d->val.funcDecl.body, numTabs + 1);
                    cout << "}" << endl;
                    break;
                case k_declKindShortDec: 
                    cout << d->val.shortDecl.id << " := " << prettyExpression(d->val.shortDecl.rhs, 0);
                    break;
                case k_declKindType: 
                    cout << "type " << d->val.typeDecl.alias1 << " " << d->val.typeDecl.alias2 << endl;
                    break;
                case k_declKindTypeStruct: 
                    cout << "type " << d->val.typeStructDecl.alias << " struct {\n";
                    // need to fix grammar
                    break;
            }
        }

        void prettyStatement(Statement *s, int numTabs) {

        }

        void prettyExpression(Expression *e, int numTabs) {

        }

        void printTabs(int numTabs) {
            for(int i = 0; i < numTabs; i++) {
                printf("    "); //4 spaces per tab;
            }
        }
}
}