#include <Core/VDComponent.h>
#include <Core/VDObject.h>
#include <DataStructure/VDPoolAllactor.h>
#include <HCQuaternion.h>
#include <HCVector3.h>
#include <malloc.h>
#include <Scene/VDGameObject.h>
#include <Scene/VDScene.h>
#include <Scene/VDTransform.h>
#include <SDL2/SDL_stdinc.h>
#include <VDSimpleType.h>
#include<Core/Math.h>
#include <cstring>

using namespace std;

VDTransform::VDTransform() {
	this->postion = VDVector3::zero();
	this->scale = VDVector3(1.0f, 1.0f, 1.0f);
	this->rotation = VDQuaternion::identity();

	this->childCount = 0;
	this->sibling = nullptr;
	this->mchild = nullptr;
	this->parent = nullptr;

	this->flag = 0;
	this->base = nullptr;
}

VDTransform::VDTransform(const VDTransform& transform){
	*this = transform;
}

VDTransform::VDTransform(const VDVector3& position, const VDQuaternion& rotation, const VDVector3& scale){
	this->postion = position;
	this->rotation = rotation;
	this->scale = scale;
	this->flag = 0;
	this->parent = nullptr;


	this->childCount = 0;
	this->sibling = nullptr;
	this->mchild = nullptr;


	this->base = nullptr;
}

VDTransform::~VDTransform(){
	if(VDScene::getScene()->nodes.isValidItem(*this)){
		VDScene::getScene()->nodes.Return(this);
	}
}

void VDTransform::initializeComponent(){

}

void VDTransform::onEnable(){

}

void VDTransform::onDisable(){

}

void VDTransform::onDestroy(){
	if(this->getParent()){
		this->getParent()->detachChild(this);
	}
	/*	*/
	if(VDScene::getScene()->nodes.isValidItem(*this)){
		VDScene::getScene()->nodes.Return(this);
	}
}

VDBehavior* VDTransform::copyComponent(unsigned int& dataSize){
	VDTransform* transform = (VDTransform*)malloc(sizeof(VDTransform));
	memcpy(transform,this, sizeof(VDTransform));
	dataSize = sizeof(VDTransform);
	return (VDBehavior*)transform;
}

VDTransform& VDTransform::operator=(const VDTransform& transform){
	VDBehavior::operator=(transform);

	this->postion = transform.postion;
	this->scale = transform.scale;
	this->rotation = transform.rotation;

	this->base  = transform.base;
	this->childCount = transform.childCount;
	this->sibling = transform.sibling;
	this->mchild = transform.mchild;

	this->parent = transform.parent;
	return *this;
}

VDTransform* VDTransform::root()const{
	if(this->getParent() == nullptr)
		return this->getParent();
	else
		return this->getParent()->root();
}

void VDTransform::rotate(const VDVector3& align){
	VDQuaternion rotation = VDQuaternion::createQuaternionOfAxis(
		fragcore::Math::deg2Rad(align.x()),
		fragcore::Math::deg2Rad(align.y()),
		fragcore::Math::deg2Rad(align.z()));
	VDQuaternion rotat = this->getRotation() * rotation;
	rotat.makeUnitQuaternion();
	this->setRotation(rotat);
}

void VDTransform::rotate(float x, float y, float z){
	this->setRotation(this->getRotation() * VDQuaternion(x,y,z));
}

void VDTransform::rotateAround(const VDVector3& align,const VDVector3& pivotPoint){
	//this->_rotation = Quaternion(this->_postion).inverse() * this->_rotation;
	//this->postion =  this->_postion * this->_rotation;
}

void VDTransform::lookAt(const VDTransform* transform){
	this->lookAt(transform->getPosition());
}

void VDTransform::lookAt(const VDGameObject* gameObject){
	lookAt(gameObject->transform());
}

void VDTransform::lookAt(const VDVector3& Target){
	//this->setRotation(VDQuaternion::lookRotation((Target - this->getPosition()), VDVector3::up()).normalize());
}

VDTransform* VDTransform::findChild(const char* name){

	if( name == nullptr ){
		return nullptr;
	}

	VDTransform* sibl = this->mchild;
	while(sibl){

		if(strcmp(sibl->gameObject()->getName(),name) == 0)
			return sibl;
		else
			sibl = sibl->sibling;
	}
	return nullptr;
}

int VDTransform::isChildOf(const VDTransform* transform)const{
	do{
		if(this->getParent()){
			if(!this->getParent())
				return SDL_TRUE;
			else
				return this->getParent()->isChildOf(transform);
		}else
			return SDL_FALSE;
	}while(SDL_TRUE);
}

void VDTransform::addChild(VDTransform* pchild){
	VDTransform* find;

	this->childCount++;
	if(!this->mchild){
		this->mchild = pchild;
		mchild->setParent( this );

	}else{

		find = this->mchild;
		while(find){
			if(find->sibling)
				find = find->sibling;
			else break;
		}
		find->sibling = pchild;
		find->sibling->setParent( this );
	}
}


void VDTransform::detachChildren(){
	/* remove children references to parent	*/
	for(unsigned int x = 0; x < this->getChildCount(); x++){
		this->child(x)->setParent( nullptr );
	}
}


void VDTransform::detachChild(VDTransform* transform){

	VDTransform* next = nullptr;

	for(unsigned int x = 0; x < this->getChildCount(); x++){
		if(transform == this->child(x)){
			/* remove child parent*/
			transform->setParent( nullptr );

			/*	relink this node children */
			this->child(x - 1)->sibling = transform->sibling;

			break;
		}
	}
}

void VDTransform::detachChild(int index){
	if(this->getChildCount() < index){
		this->detachChild(this->child(index));
	}

}
void VDTransform::detachChild(const char* name){

	unsigned int x;

	for(x = 0; x < this->getChildCount(); x++){
		if(strcmp(this->child(x)->gameObject()->getName(), name) == 0){

			this->detachChild(this->child(x));

			break;
		}
	}
}


void VDTransform::removeParent(){
	if(!this->getParent()){
		return;
	}

	// detach this transform from parent child holder
	this->getParent()->detachChild(this);
}

void VDTransform::setParent(VDTransform* parent){
	this->parent = parent;
}

VDTransform* VDTransform::getParent()const{
	return this->parent;
}

void VDTransform::translate(float x,float y,float z){
	this->setPosition(VDVector3(x,y,z));
}

int VDTransform::getChildCount()const{return this->childCount;}

VDTransform* VDTransform::child(unsigned int index)const{
	VDTransform* chi = this->mchild;
	for(int x = 0; x < index; x++){
		chi = chi->sibling;
	}
	return chi;
}

VDVector3 VDTransform::transformDirection(const VDVector3& direction)const{
	return this->getRotation().normalize().getVector(direction).normalize();
}

VDVector3 VDTransform::transformDirection(float x,float y,float z)const{
	return this->transformDirection(VDVector3(x,y,z));
}

VDVector3 VDTransform::inverseTransformDirection(const VDVector3& direction)const{
	return (this->getRotation() * (direction) * this->getRotation().conjugate()).getVector();
}

VDVector3 VDTransform::inverseTransformDirection(float x,float y,float z)const{
	return this->inverseTransformDirection(VDVector3(x,y,z));
}

void VDTransform::setPosition(const VDVector3& setPosition){

	for(int x = 0; x < this->getChildCount(); x++){
		this->child(x)->SetLocalDeltaPos(setPosition - this->postion);
	}
	this->postion = setPosition;

/*
	for(int x = this->children.size() - 1; x >= 0; x--){
		this->children[x]->SetLocalDeltaPos(setPosition - this->postion);
		continue;
	}

*/

/*		TODO fix
	if(this->base)
		this->base->PxSetGlobalPosition(this->postion);
*/

}

void VDTransform::setScale(const VDVector3& setScale){
	for(int x = this->getChildCount() - 1; x >= 0; x--){
		this->child(x)->setLocalScale(setScale);
	}
	this->scale = setScale;

}

void VDTransform::setRotation(const VDQuaternion& setRotation){
	VDQuaternion loquad;
	for(int x = this->getChildCount() - 1; x >= 0; x--){
		loquad = getRotation().inverse() * setRotation;
		loquad =  loquad * child(x)->getRotation();
		loquad.makeUnitQuaternion();

		/*	TODO make it call a function which resolve the delta movements*/
		this->child(x)->setRotation(loquad);
	}
	this->rotation = setRotation;
}

VDVector3 VDTransform::getPosition()const{
	return this->postion;
}

VDVector3 VDTransform::getScale()const{
	return this->scale;
}

VDQuaternion VDTransform::getRotation()const{
	return this->rotation;
}

// Local---

void VDTransform::setLocalPosition(const VDVector3& setPosition){

	if(this->parent){
		this->postion = this->parent->postion + setPosition;
		for(unsigned int x = 0; x < this->childCount; x++){
			//send transform position information to children.
			this->child(x)->SetLocalDeltaPos(setPosition);

		}
	}
	else
		this->postion = setPosition;

/*		TODO fix
	if(this->base)
		this->base->PxSetGlobalPosition(this->postion);
*/
}

VDVector3 VDTransform::getLocalPosition()const{
	if(this->getParent()){
		return (this->postion - this->parent->postion); // TODO calclation.
	}
	else{
		return this->postion;
	}
}

void VDTransform::setLocalRotation(const VDQuaternion& setRotation){	// setRotation * Quaternion(this->_rotation).Conjugate() * this->_rotation

	if(this->getParent()){
		VDVector3 old = this->rotation.forward();
		this->rotation = setRotation * this->rotation.conjugate() * this->rotation; // setRotation * getLocalRotation();
		this->rotation.makeUnitQuaternion();
		VDVector3 newrotat = this->rotation.forward();
		for(unsigned int x = 0; x < this->childCount; x++){			//send transform position information to children.
			this->child(x)->SetLocalRotationTransformation(this->rotation,newrotat - old);

		}
	}
	else{
		VDVector3 old = this->rotation.forward();
		this->rotation = setRotation * this->rotation.conjugate() * this->rotation; // setRotation * getLocalRotation();
		this->rotation.makeUnitQuaternion();
		VDVector3 newrotat = this->rotation.forward();
		for(unsigned int x = 0; x < this->childCount; x++){			//send transform position information to children.
		//	this->children[x]->SetLocalRotationTransformation(this->_rotation,old - newrotat);

		}
	}

}
VDQuaternion VDTransform::getLocalRotation()const{
	if(this->getParent())
		return (this->parent->rotation * VDQuaternion(this->rotation).inverse() * this->rotation).normalize();
	if(this->getParent())
		return (this->rotation * VDQuaternion(this->parent->rotation).inverse()  * this->parent->rotation).normalize(); //;
	else
		return this->rotation;
}


void VDTransform::setLocalScale(const VDVector3& localScale){
	if(this->getParent()){

		this->scale = localScale;
		for(unsigned int x = 0; x < this->childCount; x++){
			//send transform position information to children.
			this->child(x)->setLocalScale(localScale);

		}
		this->setLocalPosition(this->getLocalPosition() * localScale);
	}
	else
		this->scale = localScale;
}

VDVector3 VDTransform::getLocalScale()const{
	if(this->getParent())
		return this->scale * this->parent->scale;
	else
		return this->scale;
}


/**/
/*
VDMatrix4x4 VDTransform::getMatrix()const{
	return (VDMatrix4x4::translate(this->getPosition()) *
			VDMatrix4x4::rotate(this->getRotation()) *
			VDMatrix4x4::scale(this->getScale()));
}

VDMatrix4x4 VDTransform::getLocalMatrix()const{
	return (VDMatrix4x4)(VDMatrix4x4::translate(this->getLocalPosition()) *
			VDMatrix4x4::rotate(this->getLocalRotation()) *
			VDMatrix4x4::scale(this->getLocalScale()));
}
*/


VDMatrix4x4 VDTransform::getViewMatrix()const{
	return VDMatrix4x4();
	/*
	return (VDMatrix4x4::rotate(this->getRotation().conjugate()) *
			VDMatrix4x4::translate(-this->getPosition()));
	*/
}

VDMatrix4x4 VDTransform::getLocalViewMatrix()const{
	return VDMatrix4x4();
	/*
	return (VDMatrix4x4)(VDMatrix4x4::translate(-getLocalPosition()) *
			VDMatrix4x4::rotate(getLocalRotation().conjugate()));
	*/
}


void VDTransform::SetLocalRotationTransformation(const VDQuaternion& setRotation, const VDVector3& unitDelta){

	if(this->getParent()){
		VDVector3 old = this->rotation.forward();
		this->rotation = setRotation * this->rotation.conjugate() * this->rotation; // setRotation * getLocalRotation
		//this->_rotation = (setRotation * this->_rotation * setRotation.Inverse()) * setRotation;
		this->rotation.normalize();
		VDVector3 newrotat = this->rotation.forward();
		for(unsigned int x = 0; x < this->childCount; x++){			//send transform position information to children.
			//this->children[x]->SetLocalRotationTransformation(this->_rotation,old + newrotat);

		}
		//this->SetLocalDeltaPos(unitDelta * sqrtf(this->getLocalPosition().Magnitude()));
	}
	//else this->_rotation = setRotation;

}

void VDTransform::SetLocalDeltaPos(const VDVector3& deltaMotion){
	if(this->parent){
		this->postion += deltaMotion;
		for(unsigned int x = 0; x < this->childCount; x++){
			//send transform position information to children.
			this->child(x)->SetLocalDeltaPos(deltaMotion);

		}
	}
	else
		this->postion = deltaMotion;

/*		TODO fix
	if(this->base)
		this->base->PxSetGlobalPosition(this->postion);
*/
}

void VDTransform::SetRigidBodyPosition(const VDVector3& rigidbodyPosition){
	this->postion = rigidbodyPosition;
}

void VDTransform::SetRigidBodyRotation(const VDQuaternion& rigidbodyRotation){
	this->rotation = rigidbodyRotation;
}


VDTransform* VDTransform::createTransform(){
	VDTransform* node =  VDScene::getScene()->nodes.obtain();
	*node = VDTransform();
	return node;
}
