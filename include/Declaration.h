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
        Declaration(vector<string> ids, string type);
        
        //factored var declaration
        Declaration(vector<Declaration> decls);

        //===functions===
        Declaration(string id, vector<string> locals, Instruction body);
        Declaration(string id, vector<string> locals, string type, Instruction body);

        //===declaration with assignment===
        Declaration(vector<string> ids, vector<Expression> rhs);
        Declaration(vector<string> ids, vector<Expression>rhs, string type);

        //short declaration
        Declaration(string id, Expression rhs);

        //===type declaration
        Declaration(string alias1, string alias2);
        Declaration(string id, vector<vector<string>> structdecl_list);
}