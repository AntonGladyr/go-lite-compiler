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
		printTabs(numTabs);
		switch(s.kind) {
			case k_stmtKindForInfinite:
				break;
			case k_stmtKindForWhile:
				break;
			case k_stmtKindForThreePart:
				break;
			case k_stmtKindAssignTuple:
				cout << s.ids << " = " ;
				for(const auto& exp : s.exp_list) {
                        		prettyExpression(exp, numTabs);
					cout  << ", ";
                    		}
				cout << ";" << endl;
				break;
			case k_stmtKindAssignSelector:
				cout << s.id << "." << s.selectorId << " = " << prettyExpression(s.exp) << ";" << endl;
				// need to fix grammar
				break;
			case k_stmtKindAssignIndex:
				cout << s.id << "[" << prettyExpression(s.index) << "]"
				     << " = " << prettyExpression(exp) << ";" << endl;
				// need to fix grammar
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
				cout << "return;" << endl;
				break;
			case k_stmtKindReturnExp:
				cout << "return " << prettyExpression(s.exp, numTabs) << ";" << endl;
				break;
			case k_stmtKindBreak:
				cout << "break;" << endl;
				break;
			case k_stmtKindContinue:
				cout << "continue;" << endl;
				break;
			case k_stmtKindInc:
				cout << s.id << "++;" << endl;
				break;
			case k_stmtKindDec:
				cout << s.id << "--;" << endl;
				break;
			case k_stmtKindIncExp:
				cout << s.id << " += " << prettyExpression(s.exp, numTabs) << ";" << endl;
				break;
			case k_stmtKindDecExp:
				cout << s.id << " -= " << prettuExpression(s.exp, numTabs) << ";" << endl;
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

        void printTabs(int numTabs) {
            for(int i = 0; i < numTabs; i++) {
                printf("    "); //4 spaces per tab;
            }
        }
}
