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
		switch(s->kind) {
			case k_stmtKindForInfinite:
				break;
			case k_stmtKindForWhile:
				break;
			case k_stmtKindForThreePart:
				break;
			case k_stmtKindAssignTuple:
				break;
			case k_stmtKindAssignSelector:
				break;
			case k_stmtKindAssignIndex:
				break;
			case k_stmtKindIf:
				break;
			case k_stmtKindSwitch:
				break;
			case k_stmtKindPrint:
				break;
			case k_stmtKindPrintLn:
				break;
			case k_stmtKindReturn:
				break;
			case k_stmtKindReturnExp:
				break;
			case k_stmtKindBreak:
				break;
			case k_stmtKindContinue:
				break;
			case k_stmtKindInc:
				break;
			case k_stmtKindDec:
				break;
			case k_stmtKindIncExp:
				break;
			case k_stmtKindDecExp:
				break;
			case k_stmtSwitch:
				break;
			case k_stmtNoExpSwitch:
				break;
			case k_stmtDeclSwitch:
				break;
			case k_stmtKindIfStmt:
				break;
			case k_stmtKindDeclIfStmt:
				break;
			case k_stmtKindIfElse:
				break;
			case k_stmtKindDeclIfElse:
				break;
			case k_stmtKindIfElseNested:
				break;
			case k_stmtKindDeclIfElseNested:
				break;
		}
        }

        void prettyExpression(Expression *e, int numTabs) {

        }
}
