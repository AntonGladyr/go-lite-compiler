#ifndef RUNEEXP_CPP
#define RUNEEXP_CPP

#include <string>
#include <algorithm>
#include "RuneExp.hpp"

RuneExp::RuneExp(const std::string &_runeValue, int _lineno) : value(_runeValue), Expression(_lineno) {
	value.erase(remove(value.begin(), value.end(), '\''), value.end());
}


void RuneExp::accept(Visitor& v) {
	v.visit(this);
}

std::string RuneExp::toString() {
	std::string s = "\'";
	s.append(value);
	s.append("\'");
	return s;
}

#endif
