#include <iostream>

class VDRect;

std::istream &operator>>(std::istream &is, VDRect& r){
	return is;
}

std::ostream &operator<<(std::ostream &os, const VDRect& r){
	return os;
}
