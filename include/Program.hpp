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
		std::vector<std::shared_ptr<Declaration>> *declList;
		virtual void accept(Visitor& v) override;
	
		Program();	
                Program (const std::string &_package, std::vector<std::shared_ptr<Declaration>> *_declList) :
			package(_package), declList(_declList) { }
};

#endif
