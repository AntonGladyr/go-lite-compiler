#ifndef HASHFUNCTION_CPP
#define HASHFUNCTION_CPP

#include <string>
#include <cstring>
#include "SymbolTable/HashFunction.h"

int Hash(const std::string &s) {
	char *str = new char [s.length()+1];
	std::strcpy (str, s.c_str());
	unsigned int hash = 0;
	while (*str) hash = (hash << 1) + *str++;
	return hash % HashSize;
}

#endif
