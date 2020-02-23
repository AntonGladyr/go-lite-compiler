#ifndef TREE_H
#define TREE_H

class Node {
	public:
		int lineno;
};

class Instruction;
class Declaration;
class Statement;
class Expression;

enum StatementKind {
	k_stmtKindForInfinite,
	k_stmtKindForWhile,
	k_stmtKindForThreePart,
	k_stmtKindAssignTuple,
	k_stmtKindAssignSelector,
	k_stmtKindAssignIndex,
	k_stmtKindIf,
	k_stmtKindSwitch,
	k_stmtKindPrint,
	k_stmtKindPrintLn,
	k_stmtKindReturn,
	k_stmtKindReturnExp,
	k_stmtKindBreak,
	k_stmtKindContinue,
	k_stmtKindInc,
	k_stmtKindDec,
	k_stmtKindIncExp,
	k_stmtKindDecExp,
	k_stmtSwitch,
	k_stmtNoExpSwitch,
	k_stmtDeclSwitch,
	k_stmtKindIfStmt,
	k_stmtKindDeclIfStmt,
	k_stmtKindIfElse,
	k_stmtKindDeclIfElse,
	k_stmtKindIfElseNested,
	k_stmtKindDeclIfElseNested

};

enum ExpressionKind {
		//Binary
            k_expKindMinus,
            k_expKindPlus,
            k_expKindMultiply,
            k_expKindDivide,
            k_expKindModulo,
            k_expKindBitAnd,
            k_expKindBitOr,
            k_expKindBitXor,
            k_expKindBitClear,
            k_expKindLeftShift,
            k_expKindRightShift,
            k_expKindIsEqual,
            k_expKindIsNotEqual,
            k_expKindLessThan,
            k_expKindLessThanEqual,
            k_expKindGreaterThan,
            k_expKindGreaterThanEqual,
            k_expKindAnd,
            k_expKindOr,
		//Unary
 	    k_expKindUMinus,
            k_expKindUNot,
            k_expKindUPLUS,
            k_expKindUXOR,
		//Literals
	    k_expKindBoolean,
	    k_expKindInteger,
 	    k_expKindString,
	    k_expKindRune,
	    k_expKindFloat,
		//Buildins 
	    k_expKindAppend,
	    k_expKindLen,
	    k_expKindCap
};

enum DeclarationKind {
    k_declKindDeclare,
    k_declKindAssign,
    k_declKindFactor,
    k_declKindFunc,
    k_declKindShortDec,
    k_declKindType,
    k_declKindTypeStruct
};

enum InstructionKind {
    k_insKindDecl,
    k_insKindStmt
};

#endif
