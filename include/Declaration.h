#ifndef DECLARATION_H 
#define DECLARATION_H

#include <vector>
#include <string>

#include "tree.h"

class Declaration : Node {
    public:
        DeclarationKind kind;
        union val {
            struct { std::vector<std::string> ids; std::string type; } declareDecl;
            struct { std::vector<std::string> ids; std::vector<Expression> rhs; std::string type; } assignDecl;
            struct { std::vector<Declaration> decls; } factorDecl;
            struct { std::string id; std::vector<std::string> locals; std::string type; Instruction *body; } funcDecl;
            struct { std::string id; Expression *rhs; } shortDecl;
            struct { std::string alias1; std::string alias2; } typeDecl;
            struct { std::string alias; std::vector<std::vector<std::string>> structdecl_list; } typeStructDecl;
        };

        //declaration without initialization
        Declaration(std::vector<std::string> ids, std::string type);
        
        //factored var declaration
        Declaration(std::vector<Declaration> decls);

        //===functions===
        Declaration(std::string id, std::vector<std::string> locals, Instruction *body);
        Declaration(std::string id, std::vector<std::string> locals, std::string type, Instruction *body);

        //===declaration with assignment===
        Declaration(std::vector<std::string> ids, std::vector<Expression> rhs);
        Declaration(std::vector<std::string> ids, std::vector<Expression>rhs, std::string type);

        //short declaration
        Declaration(std::string id, Expression *rhs);

        //===type declaration
        Declaration(std::string alias1, std::string alias2);
        Declaration(std::string id, std::vector<std::vector<std::string>> structdecl_list);
}

#endif 