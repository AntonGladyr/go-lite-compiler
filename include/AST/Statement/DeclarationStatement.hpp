#ifndef DECLSTMT_HPP
#define DECLSTMT_HPP

#include <utility>
#include <string>
#include "Services/Visitor.hpp"
#include "AST/Declaration/VariableDeclaration.hpp"
#include "AST/Statement/Statement.hpp"

class VariableDeclaration;

class DeclarationStatement : public Statement {
	public:
		VariableDeclaration *decl = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();

		DeclarationStatement(
			VariableDeclaration *_decl,
			int _lineno
		) : decl(_decl), Statement(_lineno) { }
	
		DeclarationStatement() { }
		~DeclarationStatement();
};

#endif
