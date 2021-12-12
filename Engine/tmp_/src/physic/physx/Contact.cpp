#define USE_PHYSX
#include"VDContact.h"
#include<physx/PxPhysicsAPI.h>

VDContact::VDContact(const VDContact& contact) {
	this->count = contact.count;
	this->pcontact = contact.pcontact;
}

VDContact::VDContact() {
	this->count = 0;
	this->pcontact = nullptr;
}

unsigned int VDContact::getCount() const {
	return this->count;
}

VDVector3 VDContact::impulse(int index) const {
	return *VDCASTP(VDVector3*,
	        & VDCASTP(physx::PxContactPairPoint*,pcontact)[index].impulse);
}

VDVector3 VDContact::point(int index) const {
	return *VDCASTP(VDVector3*,
	        & VDCASTP(physx::PxContactPairPoint*,pcontact)[index].position);
}

VDVector3 VDContact::normal(int index) const {
	return *VDCASTP(VDVector3*,
	        & VDCASTP(physx::PxContactPairPoint*,pcontact)[index].normal);
}

float VDContact::distance(int index) const {
	return VDCASTP(physx::PxContactPairPoint*,pcontact)[index].impulse.magnitude();
}
