#include <Core/VDTypes.h>
#include <string.h>
#include <typeinfo>

using namespace std;

VDTypeInfo::VDTypeInfo(void){
	this->type = NULL;
	this->typeSize = 0;

}

VDTypeInfo::VDTypeInfo(const VDTypeInfo& type){
	*this = type;
}

VDTypeInfo::VDTypeInfo(const std::type_info& _type, long unsigned int size){
	this->type = (std::type_info*)&_type;
	this->typeSize = size;
}

VDTypeInfo::VDTypeInfo(const std::type_info& _type){
	this->type = (std::type_info*)&_type;
	this->typeSize = 0;
}

bool VDTypeInfo::isInherited(const VDTypeInfo& type)const{
	return this->type->before(*type.getType());
}

bool VDTypeInfo::operator==(const VDTypeInfo* rh){
	return (this == rh);
}
bool VDTypeInfo::operator!=(const VDTypeInfo* rh){
	return (this != rh);
}
bool VDTypeInfo::operator==(const std::type_info& ptype)const{
	return (*this->type == ptype);
}
bool VDTypeInfo::operator!=(const std::type_info& ptype)const{
	return (*this->type != ptype);
}
bool VDTypeInfo::operator==(unsigned int rh){
	return (this->type->hash_code() == rh);
}
bool VDTypeInfo::operator!=(unsigned int  rh){
	return (this->type->hash_code() != rh);
}

bool VDTypeInfo::isPointer(void)const{
	return type->__is_pointer_p();
}

bool VDTypeInfo::isFunction(void)const{
	return type->__is_function_p();
}

const char* VDTypeInfo::getName(void)const{
	return type->name();
}

VDTypeInfo& VDTypeInfo::operator=(const VDTypeInfo& type){
	this->setType( type.getType() );
	this->setTypeSize( type.getTypeSize() );
	return *this;
}

