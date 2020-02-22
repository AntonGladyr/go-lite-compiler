class Declaration : public Node {
    public:
        DeclarationKind kind;
        union val {
            struct { vector<string> ids; string type; } declareDecl;
            struct { vector<string> ids; vector<Expression> rhs; string type; } assignDecl;
            struct { vector<Declaration> decls; } factorDecl;
            struct { string id; vector<string> locals; string type; Instruction body; } funcDecl;
            struct { string id; Expression rhs; } shortDecl;
            struct { string alias1; string alias2; } typeDecl;
            struct { string alias; vector<vector<string>> structdecl_list; } typeStructDecl;
        }

        //declaration without initialization
        Declaration(vector<string> ids, string type) : kind{k_declKindDeclare} {
            val.declareDecl.ids = ids;
            val.declareDecl.type = type;
        }

        //factored var declaration
        Declaration(vector<Declaration> decls) : kind{k_declKindFactor}, val.factorDecl{decls} {
            factorDecl.decls = decls;
        }

        //===functions===
        Declaration(string id, vector<string> locals, Instruction body) : Declaration{id, locals, NULL, body} { }

        Declaration(string id, vector<string> locals, string type, Instruction body) : kind{k_declKindFunc} {
            funcDecl.id = id;
            funcDecl.locals = locals;
            funcDecl.type = type;
            funcDecl.body = body;
        }
        //===! functions===

        //===declaration with assignment===
        Declaration(vector<string> ids, vector<Expression> rhs) 
            : Declaration {ids, rhs, "<infer>", lineno} { }

        Declaration(vector<string> ids, vector<Expression>rhs, string type) 
            : kind{k_declKindAssign} {
            if(ids.size() != rhs.size()) {
                printf("Error: (line %d) number of assignments does not agree with the number of identifiers", lineno);
                exit(1);
            }

            val.assignDecl.ids = ids;
            val.assignDecl.rhs = rhs;
            val.assignDecl.type = type;
        }
        //===! declaration with assignment ===

        //short declaration
        Declaration(string id, Expression rhs) : kind{k_declKindShortDec} {
            val.shortDecl.id = id;
            val.shortDecl.rhs = id;
        }

        //===type declaration
        Declaration(string alias1, string alias2) : kind{k_declKindType} {
            val.typeDecl.alias1 = alias1;
            val.typeDecl.alias2 = alias2;
        }

        Declaration(string id, vector<vector<string>> structdecl_list) : kind{k_declKindTypeStruct} {
            val.typeStructDecl.id = id;
            val.typeStructDecl.structdecl_list = structdecl_list;
        }
}