#ifndef FUNCTIONDECLARATION_HPP
#define FUNCTIONDECLARATION_HPP

#include <vector>
#include <string>
#include <utility>
#include "Services/Visitor.hpp"
#include "AST/Declaration/Declaration.hpp"
#include "AST/Statement/Statement.hpp"
#include "AST/Statement/BlockStatement.hpp"

class BlockStatement;
typedef std::pair<std::string, std::pair<std::string, std::vector<int>*>*> param_type;

class FunctionDeclaration : public Declaration {
	public:
		std::string id;
		std::vector<param_type*> *params = NULL;
		std::pair<std::string, std::vector<int>*> *type = NULL;
		BlockStatement *blockStmt = NULL;

		virtual void accept(Visitor& v) override;
		virtual std::string toString();
		
		FunctionDeclaration(
			const std::string &_id,
			std::vector<param_type*> *_params,
			BlockStatement *_blockStmt,
			int _lineno
		) : id(_id), params{_params}, blockStmt{_blockStmt}, Declaration(_lineno) { }
		
		FunctionDeclaration(
			const std::string &_id,
			std::vector<param_type*> *_params,
			std::pair<std::string, std::vector<int>*> *_type,
			BlockStatement *_blockStmt,
			int _lineno
		) : id(_id), params{_params}, type(_type), blockStmt{_blockStmt}, Declaration(_lineno) { }
		
		FunctionDeclaration() { }
		~FunctionDeclaration();
};

#endif
