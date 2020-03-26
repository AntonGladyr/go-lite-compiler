#ifndef RUNEEXP_CPP
#define RUNEEXP_CPP

#include <algorithm>
#include <sstream>
#include "AST/Expression/RuneExp.hpp"

RuneExp::RuneExp(const std::string &_runeValue, int _lineno) : value(_runeValue), Expression(_lineno) {
	value.erase(remove(value.begin(), value.end(), '\''), value.end());
}


void RuneExp::accept(Visitor& v) {
	//v.visit(this);
}

std::string RuneExp::toString() {
	std::stringstream ss;
	ss << "\'" << value << "\'";
	return ss.str();
}

#endif
