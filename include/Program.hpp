#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <string>
#include <vector>
#include <memory>
#include "Node.hpp"
#include "Declaration.hpp"

class Program : public Node {
	public:
		std::string package;
		//std::vector<std::shared_ptr<Declaration>> *declList;
		std::vector<Declaration*> *declList;
		virtual void accept(Visitor& v) override;
	
		Program() { }
		~Program();
                /*program (const std::string &_package, std::vector<std::shared_ptr<Declaration>> *_decllist) :
			package(_package), decllist(_decllist) { }*/
		Program(const std::string &_package, std::vector<Declaration*> *_decllist) :
			package(_package), declList(_decllist) { }

};

#endif
