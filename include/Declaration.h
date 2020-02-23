#ifndef DECLARATION_H 
#define DECLARATION_H

#include <vector>
#include <string>

#include "tree.h"
#include "Node.hpp"

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
        Declaration(std::vector<std::string> ids, std::string type)
		: kind{k_declKindDeclare}, val.declareDecl.ids{ids}, val.declareDecl.type{type};
        
        //factored var declaration
        Declaration(std::vector<Declaration*> decls) : kind{k_declKindFactor}, val.factorDecl{decls};

        //===functions===
        Declaration(std::string id, std::vector<std::string> locals, string type, Instruction *body)
		: kind{k_declKindFunc}, funcDecl.id{id}, funcDecl.locals{locals}, funcDecl.type{type}, funcDecl.body{body};
	
        //===declaration with assignment===
	//TODO: catching errors: number of assignments does not agree with the number of identifiers
        Declaration(std::vector<std::string> ids, std::vector<Expression*> rhs)
		: kind{k_declKindAssign}, val.assignDecl.ids{ids}, val.assignDecl.rhs{rhs}, val.assignDecl.type{type};
        
        //short declaration
        Declaration(std::string id, Expression *rhs)
		: kind{k_declKindShortDec}, val.shortDecl.id{id}, val.shortDecl.rhs{rhs};

        //type declaration
        Declaration(std::string alias1, std::string alias2)
		: kind{k_declKindType}, val.typeDecl.alias1{alias1}, val.typeDecl.alias2{alias2};
        Declaration(std::string id, std::vector<std::vector<std::string>> structdecl_list)
		: kind{k_declKindTypeStruct}, val.typeStructDecl.id{id}, val.typeStructDecl.structdecl_list{structdecl_list} ;
};

#endif 
