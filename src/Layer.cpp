#include <Core/VDLayer.h>
#include <cstring>
#include <map>
#include <utility>

struct cmp_str{
   bool operator()(char const *a, char const *b){
      return std::strcmp(a, b) < 0;
   }
};
std::map<char*, unsigned int, cmp_str> layer_names;


VDLayer::VDLayer(void){
	this->index = 0;
}

VDLayer::VDLayer(const VDLayer& layer){
	this->setIndex(layer.getIndex());
}

VDLayer::VDLayer(unsigned int index){
	this->index = index;
}

unsigned int VDLayer::getIndex(void)const{
	return this->index;
}

void VDLayer::setIndex(unsigned int index){
	this->index = index;
}

VDLayer& VDLayer::operator<<(int i){
	this->index <<= i;
	return *this;
}

VDLayer& VDLayer::operator>>(int i){
	this->index >>= i;
	return *this;
}

VDLayer VDLayer::operator&(const VDLayer& layer)const{
	return VDLayer(getIndex() & layer.getIndex());
}

unsigned int VDLayer::operator!(void)const{
	return !this->index;
}

bool VDLayer::operator==(const VDLayer& layer)const{
	return (index == layer.getIndex());
}

bool VDLayer::operator!=(const VDLayer& layer)const{
	return (index  != layer.getIndex());
}
void VDLayer::setIndextName(unsigned int index, const char* cname){
	//layer_names.insert(std::pair<char*, unsigned int>( (char*)cname, index ));
}

const char* VDLayer::getIndexName(unsigned int index){
	return layer_names.begin()->first;	/*	TODO resolve*/
}

VDLayer VDLayer::getIndexByName(const char* cname){
	//return VDLayer(layer_names[(char*)cname]);
}
