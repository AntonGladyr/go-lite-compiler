#ifndef TREE_H
#define TREE_H

class Node;
class Instruction;
class Declaration;
class Statement;
class Expression;

enum StatementKind {
	k_stmtKindFor,
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