enum StatementKind {
	k_stmtKindFor,
	k_stmtKindAssign,
	k_stmtKindIf,
	k_stmtKindSwitch,
	k_stmtKindPrint,
	k_stmtKindReturn,
	k_stmtKindBreak,
	k_stmtKindContinue
}

enum AssignStatementKind {
	k_AssignStmtKindTuple,
	k_AssignStmtKindSelector,
	k_AssignStmtKindIndex
}

enum DeclarationKind {
    k_declKindDeclare,
    k_declKindAssign,
    k_declKindFactor,
    k_declKindFunc,
    k_declKindShortDec,
    k_declKindType,
    k_declKindTypeStruct
}

enum InstructionKind {
    k_insKindDecl,
    k_insKindStmt
}
