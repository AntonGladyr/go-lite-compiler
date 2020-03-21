#include <iostream>
#include "Expression.hpp"

using std::ostream;

ostream& operator<< (ostream& o, const Expression& exp) {
    return exp.toString(o);
}
