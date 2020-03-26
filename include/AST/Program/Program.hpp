#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <string>
#include <vector>
#include "Services/Visitor.hpp"
#include "AST/Declaration/Declaration.hpp"
#include "AST/Node.hpp"

class Declaration;
class Visitor;
class Node;

class Program : public Node {
	public:
		std::string package;
		//std::vector<std::shared_ptr<Declaration>> *declList;
		std::vector<Declaration*> *declList;	
		
		void accept(Visitor& v);
		virtual std::string toString();
			
		Program(
			const std::string &_package,
			std::vector<Declaration*> *_declList,
			int _lineno
		) : package(_package), declList(_declList), Node(_lineno) { }
		
		Program() { }
		~Program();

};

#endif
