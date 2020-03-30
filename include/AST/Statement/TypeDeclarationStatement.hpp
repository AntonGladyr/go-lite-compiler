#ifndef TYPEDECLSTMT_HPP
#define TYPEDECLSTMT_HPP

#include <utility>
#include <string>
#include "Services/Visitor.hpp"
#include "AST/Declaration/TypeDeclaration.hpp"
#include "AST/Statement/Statement.hpp"

class TypeDeclaration;

class TypeDeclarationStatement : public Statement {
	public:
		TypeDeclaration *typeDecl = NULL;
		
		virtual void accept(Visitor& v) override;
		virtual std::string toString();

		TypeDeclarationStatement(
			TypeDeclaration *_typeDecl,	
			int _lineno
		) : typeDecl(_typeDecl), Statement(_lineno) { }
		
		TypeDeclarationStatement() { }
		~TypeDeclarationStatement();
};

#endif
