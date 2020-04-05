#ifndef TYPENAME_HPP
#define TYPENAME_HPP

#include <vector>
#include <string>

class TypeName {
	public:
		std::string name;
		std::vector<int> *indexes = NULL;
		int lineno;
		
		TypeName(
			const std::string &_name,
			std::vector<int> *_indexes,
			int _lineno
		) : name(_name), indexes(_indexes), lineno(_lineno) { }
		
		TypeName() { }
		~TypeName();
};

#endif
