#include <DataStructure/VDPoint.h>
#include <iostream>

using namespace std;

std::istream &operator>>(std::istream& is, VDPoint& t){
    int temp;
    is >> temp;
    t.m[0] = temp;
    is >> temp;
    t.m[1] = temp;
    return is;
}
std::ostream &operator<<(std::ostream& os, const VDPoint& t){
    os << '('
       << t.m[0] << " "
       << t.m[1] << ')';
    return os;
}
