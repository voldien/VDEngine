#include <iostream>

class VDSize;


std::istream &operator>>(std::istream &is, const VDSize& t){
	return is;
}

std::ostream &operator<<(std::ostream &os, const VDSize& t){
	return os;
}

