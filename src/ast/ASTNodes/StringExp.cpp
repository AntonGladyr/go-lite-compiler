#ifndef STRINGEXP_CPP
#define STRINGEXP_CPP

#include <algorithm>
#include "StringExp.hpp"

void StringExp::findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr) {
	// Get the first occurrence
	size_t pos = data.find(toSearch);
	// Repeat till end is reached
	while( pos != std::string::npos)
	{
		// Replace this occurrence of Sub String
		data.replace(pos, toSearch.size(), replaceStr);
		// Get the next occurrence from the current position
		pos = data.find(toSearch, pos + replaceStr.size());
	}
}

StringExp::StringExp(const std::string &_stringValue, int _lineno) : value(_stringValue), Expression(_lineno) {
	if (value.front() == '\"' && value.back() == '\"')
		value.erase(remove(value.begin(), value.end(), '\"'), value.end());
	else /* `raw string` */{
		value.erase(remove(value.begin(), value.end(), '`'), value.end());
		findAndReplaceAll(value, "\\", "\\\\");
		findAndReplaceAll(value, "\"", "\\\"");
		findAndReplaceAll(value, "\?", "\\\?");	
		findAndReplaceAll(value, "\a", "\\a");
		findAndReplaceAll(value, "\b", "\\b");	
		findAndReplaceAll(value, "\f", "\\f");
		findAndReplaceAll(value, "\n", "\\n");
		findAndReplaceAll(value, "\r", "\\r");
		findAndReplaceAll(value, "\t", "\\t");
		findAndReplaceAll(value, "\v", "\\v");
	}
}

void StringExp::accept(Visitor& v) {
	v.visit(this);
}

std::string StringExp::toString() {
	std::string res;
	res.append("\"");
	res.append(value);
	res.append("\"");
	return res;
}

#endif
