#include <Rendering/VDColor32.h>
#include <iostream>


std::istream& operator>>(std::istream &is, VDColor32& t){
	return is;
}

std::ostream& operator<<(std::ostream &os, const VDColor32& t){
	return os;
}
