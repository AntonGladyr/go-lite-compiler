#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <string>
#include <vector>
#include "Services/Visitor.hpp"
#include "AST/Declaration/Declaration.hpp"
#include "AST/Expression/IdentifierExp.hpp"
#include "AST/Node.hpp"

class Declaration;
class Visitor;
class IdentifierExp;
class Node;

class Program : public Node {
	public:
		IdentifierExp *package = NULL;
		//std::vector<std::shared_ptr<Declaration>> *declList;
		std::vector<Declaration*> *declList = NULL;
		
		void accept(Visitor& v);
		virtual std::string toString();
	
		Program(
			IdentifierExp *_package,
			std::vector<Declaration*> *_declList,
			int _lineno
		) : package(_package), declList(_declList), Node(_lineno) { }
		
		Program() { }
		~Program();

};

#endif
