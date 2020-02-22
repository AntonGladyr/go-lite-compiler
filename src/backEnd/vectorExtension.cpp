#include <vector>
#include <iostream>

using std::vector;
using std::ostream;

template<typename T>
ostream& operator<< (ostream& out, const vector<T>& v) {
    size_t last = v.size() - 1;
    for(size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last) 
            out << ", ";
    }
    return out;
}