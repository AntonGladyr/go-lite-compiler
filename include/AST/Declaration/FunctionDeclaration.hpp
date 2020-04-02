#ifndef FUNCTIONDECLARATION_HPP
#define FUNCTIONDECLARATION_HPP

#include <vector>
#include <string>
#include <utility>
#include "Services/Visitor.hpp"
#include "AST/Declaration/Declaration.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Statement/BlockStatement.hpp"
#include "AST/Expression/IdentifierExp.hpp"

class BlockStatement;
class IdentifierExp;
//pair<id, pair<type, indexes>>
typedef std::pair<IdentifierExp*, std::pair<std::string, std::vector<int>*>*> param_type;

class FunctionDeclaration : public Declaration {
	public:
		IdentifierExp *idExp = NULL;
		std::vector<param_type*> *params = NULL;
		std::pair<std::string, std::vector<int>*> *type = NULL;
		BlockStatement *blockStmt = NULL;
		
		std::pair<std::string, std::vector<int>*> getType() { return *type; }
		std::string symbolSignatureToStr();
		virtual void accept(Visitor& v) override;
		virtual std::string symbolToStr() override ;
		virtual std::string symbolTypeToStr() override;
		virtual std::string toString();
		
		FunctionDeclaration(
			IdentifierExp *_idExp,
			std::vector<param_type*> *_params,
			BlockStatement *_blockStmt,
			int _lineno
		) : idExp(_idExp), 
		    params{_params},
		    blockStmt{_blockStmt},
		    Declaration(_lineno) { };
		
		FunctionDeclaration(
			IdentifierExp *_idExp,
			std::vector<param_type*> *_params,
			std::pair<std::string, std::vector<int>*> *_type,
			BlockStatement *_blockStmt,
			int _lineno
		) : idExp(_idExp), 
		    params{_params},
		    type(_type),
		    blockStmt{_blockStmt},
		    Declaration(_lineno) { };
		
		FunctionDeclaration() { }
		~FunctionDeclaration();
};

#endif
