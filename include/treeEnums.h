enum StatementKind {
    k_stmtKindFor,
    k_stmtKindAssign
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