#ifndef PRETTYPRINTER_CPP
#define PRETTYPRINTER_CPP

#include <sstream>
#include <iostream>
#include "Services/PrettyPrinter.hpp"

void PrettyPrinter::visit(Program *prg) {
	if (prg == NULL) return;
	std::cout << prg->toString();	
}

void PrettyPrinter::visit(VariableDeclaration *varDecl) {
	if (varDecl == NULL) return;
	std::cout << getTabs() << varDecl->toString();
}

void PrettyPrinter::visit(TypeDeclaration *typeDecl) {
	if (typeDecl == NULL) return;
	std::cout << getTabs() << typeDecl->toString();
}

void PrettyPrinter::visit(FunctionDeclaration *funcDecl) {
	if (funcDecl == NULL) return;
	std::cout << getTabs() << funcDecl->toString();
}

void PrettyPrinter::visit(BlockStatement *blockStmt) {
	if (blockStmt == NULL) return;
	
	if (isScopeOpened) {
		std::cout << getTabs() << "{" << std::endl;
		numTabs++;
	} else {
		numTabs--;
		std::cout << getTabs() << "}" << std::endl;
	}
}

void PrettyPrinter::visit(ReturnStatement *returnStmt) {
	if (returnStmt == NULL) return;
	std::cout << getTabs() << returnStmt->toString();
}

std::string PrettyPrinter::getTabs() {
	std::stringstream ss;
	for(int i = 0; i < numTabs; i++) {
		ss << "\t";
	}
	return ss.str();
}

/*void PrettyPrinterVisitor::visit(IntegerExp *intExp) {
	if (intExp == NULL) return;
	std::cout << intExp;
} 

void PrettyPrinterVisitor::visit(FloatExp *floatExp) {
	if (floatExp == NULL) return;
	std::cout << floatExp;
} 

void PrettyPrinterVisitor::visit(StringExp *stringExp) {
	if (stringExp == NULL) return;
	std::cout << stringExp;
} 

void PrettyPrinterVisitor::visit(BoolExp *boolExp) {
	if (boolExp == NULL) return;
	std::cout << boolExp;
}

void PrettyPrinterVisitor::visit(RuneExp *runeExp) {
	if (runeExp == NULL) return;
	std::cout << runeExp->toString();
}*/


/*

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
				cout << "for ";
				prettyInstruction(s.body, numTabs + 1);
				break;
			case k_stmtKindForWhile:
				cout << "for " << prettyExpression(s.exp, numTabs);
				prettyInstruction(s.body, numTabs + 1);
				break;
			case k_stmtKindForThreePart:
				cout << "for ";
				prettyInstruction(s.initStmt, numTabs);
				cout << ";" << prettyExpression(s.condition, numTabs) << ";"
				     << prettyStatement(s.postStmt, numbTabs) << " ";
				prettyInstruction(s.body, numTabs + 1);
				// need to fix grammar (parentheses) 
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
				cout << s.id << "." << s.selectorId << " = " 
				     << prettyExpression(s.exp, numTabs) << ";" << endl;
				// need to fix grammar (multiple selectors)
				break;
			case k_stmtKindAssignIndex:
				cout << s.id << "[" << prettyExpression(s.index, numTabs) << "]"
				     << " = " << prettyExpression(s.exp, numTabs) << ";" << endl;
				// need to fix grammar (multiple indexes)
				break;
			case k_stmtKindPrint:
				cout << "print(";
				for(const auto& exp : s.exp_list) {
                        		prettyExpression(exp, numTabs);
					if (exp != s.exp_list.end()) cout  << ", ";
                    		}
				cout << ")"
				break;
			case k_stmtKindPrintLn:
				cout << "println(";
				for(const auto& exp : s.exp_list) {
                        		prettyExpression(exp, numTabs);
					if (exp != s.exp_list.end()) cout  << ", ";
                    		}
				cout << ")"
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
				cout << s.id << "--;" << 
;
				break;
			case k_stmtKindIncExp:
				cout << s.id << " += " << prettyExpression(s.exp, numTabs) << ";" << endl;
				break;
			case k_stmtKindDecExp:
				cout << s.id << " -= " << prettyExpression(s.exp, numTabs) << ";" << endl;
				break;
			case k_stmtNoExpSwitch:	
				cout << "switch {" << endl;
				for(const auto& caseItem: s.case_list) {
					printTabs(numTabs + 1);
					cout << "case " << prettyExpression(std::get<0>(caseItem)) << " : "
					     << prettyInstruction(std::get<1>(caseItem)) << end;
                    		}
				cout << "}" << endl;
				//TODO fix default clause
				//need to fix grammar (mutiple expressions in case)
				break;
			case k_stmtSwitch:
				cout << "switch " << prettyExpression(s.exp) << " {" << endl;
				for(const auto& caseItem: s.case_list) {
					printTabs(numTabs + 1);
					cout << "case " << prettyExpression(std::get<0>(caseItem)) << " : "
					     << prettyInstruction(std::get<1>(caseItem)) << endl;
                    		}
				cout << "}" << endl;
				//TODO fix default clause
				//need to fix grammar (mutiple expressions in case)
				break;
			case k_stmtDeclSwitch:
				cout << "switch " << prettyDeclaration(s.decl) << " {" << endl;
				for(const auto& caseItem: s.case_list) {
					printTabs(numTabs + 1);
					cout << "case " << prettyExpression(std::get<0>(caseItem)) << " : "
					     << prettyInstruction(std::get<1>(caseItem)) << endl;
                    		}
				cout << "}" << endl;
				//TODO fix default clause
				//need to fix grammar (mutiple expressions in case)
				break;
			case k_stmtKindIfStmt:
				cout << "if " << prettyExpression(s.exp, numTabs);
				prettyInstruction(s.ins);
				break;
			case k_stmtKindDeclIfStmt:
				cout << "if " << prettyDeclaration(s.decl, numTabs);
				prettyInstruction(s.ins);
				break;
			case k_stmtKindIfElse:
				cout << "if " << prettyExpression(s.exp, numTabs);
				prettyInstruction(s.ins);
				cout << "else ";
				prettyInstruction(s.elseIns);
				break;
			case k_stmtKindDeclIfElse:
				cout << "if " << prettyExpression(s.expm);
				break;
			case k_stmtKindIfElseNested:
				break;
			case k_stmtKindDeclIfElseNested:
				break;
		}
        }

        void prettyExpression(Expression *e) {
		switch (e->kind_): 
			case k_expKindMinus:
				cout << "("
				prettyExpression(e.left_operand_);
				cout << "-";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

			case k_expKindPlus:

				cout << "("
				prettyExpression(e.left_operand_);
				cout << "+";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

            		case k_expKindMultiply:
				
				cout << "("
				prettyExpression(e.left_operand_);
				cout << "*";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

            		case k_expKindDivide:
				
				cout << "("
				prettyExpression(e.left_operand_);
				cout << "/";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

           		case k_expKindModulo:
				
				cout << "("
				prettyExpression(e.left_operand_);
				cout << "%";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

            		case k_expKindBitAnd:
				
				cout << "("
				prettyExpression(e->left_operand_);
				cout << "&";
				prettyExpression(e->right_operand_)
				cout << ")"
				break;;

            		case k_expKindBitOr:
				
				cout << "("
				prettyExpression(e.left_operand_);
				cout << "|";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

           		case k_expKindBitXor:
				
				cout << "("
				prettyExpression(e.left_operand_);
				cout << "^";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

           		case k_expKindBitClear:
				
				cout << "("
				prettyExpression(e.left_operand_);
				cout << "&^";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;
            		case k_expKindLeftShift:
				
				cout << "("
				prettyExpression(e.left_operand_);
				cout << "<<";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

            		case k_expKindRightShift:
				
				cout << "("
				prettyExpression(e.left_operand_);
				cout << ">>";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;
           		case k_expKindIsEqual:
				
				cout << "("
				prettyExpression(e.left_operand_);
				cout << "==";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

            		case k_expKindIsNotEqual:
				
				cout << "("
				prettyExpression(e.left_operand_);
				cout << "!=";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

           		case  k_expKindLessThan:
				
				cout << "("
				prettyExpression(e.left_operand_);
				cout << "<";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

            		case k_expKindLessThanEqual:

				cout << "("
				prettyExpression(e.left_operand_);
				cout << "<=";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

            		case k_expKindGreaterThan:
				
				cout << "("
				prettyExpression(e.left_operand_);
				cout << ">";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

            		case k_expKindGreaterThanEqual:

				cout << "("
				prettyExpression(e.left_operand_);
				cout << ">=";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

           		case k_expKindAnd:

				cout << "("
				prettyExpression(e.left_operand_);
				cout << "&&";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

           		case  k_expKindOr:

				cout << "("
				prettyExpression(e.left_operand_);
				cout << "||";
				prettyExpression(e.right_operand_)
				cout << ")"
				break;

 	    		case k_expKindUMinus:
				cout << "("
				cout << "-";
				prettyExpression(e.operand_)
				cout << ")"
				break;
            		case k_expKindUNot:
				cout << "("
				cout << "!";
				prettyExpression(e.operand_)
				cout << ")"
				break;
           		case k_expKindUPLUS:
				cout << "("
				cout << "+";
				prettyExpression(e.operand_)
				cout << ")"
				break;
            		case k_expKindUXOR:
				cout << "("
				cout << "^";
				prettyExpression(e.operand_)
				cout << ")"
				break;
			//literals
			case k_expKindBoolean:
				
				cout << (e.valueBool)
				break;

	   		case k_expKindInteger:
				cout << (e.valueInt)
				break;
 	    		case k_expKindString:
				cout << (e.valueChar)
				break;
	    		case k_expKindRune:
				cout << (e.valueChar)
				break;
	    		case k_expKindFloat:
				cout << (e.valueFloat)
				break;
				//Buildins 
		
	    		case k_expKindAppend:
				cout << "append"
				cout << "(";
				prettyExpression(e.val.left_expression_)
				cout << ",";
				prettyExpression(e.val.right_expression_)
				cout << ")"
				break;
	    		case k_expKindLen:
				cout << "len"
				cout << "(";
				prettyExpression(e.expression_)
				cout << ")"
				break;
	    		case k_expKindCap:
				cout << "cap";
				cout << "("; ;
				prettyExpression(e.expression_)
				cout << ")" ;
				break;
 };

        }

*/

#endif
