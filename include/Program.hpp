#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <string>
#include <vector>
#include <memory>
#include "Visitor.hpp"
#include "Declaration.hpp"
#include "Node.hpp"

class Declaration;
class Visitor;
class Node;

class Program : public Node {
	public:
		std::string package;
		//std::vector<std::shared_ptr<Declaration>> *declList;
		std::vector<Declaration*> *declList;
		//virtual void accept(Visitor& v) override;
		void accept(Visitor& v);
			
		Program() { }
		~Program();
                /*program (const std::string &_package, std::vector<std::shared_ptr<Declaration>> *_decllist) :
			package(_package), decllist(_decllist) { }*/
		Program(const std::string &_package, std::vector<Declaration*> *_declList, int _lineno) :
			package(_package), declList(_declList), Node(_lineno) { }

};

#endif
