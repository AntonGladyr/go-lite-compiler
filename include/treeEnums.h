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
