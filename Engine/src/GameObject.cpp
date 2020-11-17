#include <Animation/VDAnimation.h>
#include <Audio/VDAudioSource.h>
#include <Core/VDBehavior.h>
#include <Core/VDComponent.h>
#include <Core/VDDebug.h>
#include <Core/VDLayer.h>
#include <Core/VDObject.h>
#include <Core/VDTypes.h>
#include <Physic/VDBoxCollider.h>
#include <Physic/VDPlaneCollider.h>
#include <Physic/VDRigidBody.h>
#include <Rendering/VDCamera.h>
#include <Rendering/VDLight.h>
#include <Rendering/VDRender.h>
#include <stdlib.h>
#include <Scene/VDCameraController.h>
#include <Scene/VDGameObject.h>
#include <Scene/VDScene.h>
#include <Scene/VDTransform.h>
#include <SDL2/SDL_stdinc.h>
#include <VDDef.h>
#include <VDSimpleType.h>
#include <cassert>
#include <cstring>
#include <iterator>
#include <list>
#include <typeinfo>
#include <vector>

using namespace std;

list<VDGameObject*> gSerlizedGameObject;

VDGameObject::VDGameObject(int serizlized) : VDObject(){
	this->addComponet(VDTransform::createTransform());
	this->layer = VDLayer::getIndexByName("all");
	this->active = eActive;
	this->setName("GameObject");
	this->initialize(serizlized);
}

VDGameObject::VDGameObject(const VDGameObject& object){
	*this = object;
}

VDGameObject::VDGameObject(const char* cName) : VDObject(){
	this->addComponet(VDTransform::createTransform());
	this->setName(cName);
	this->layer = VDLayer::getIndexByName("all");
	this->active = eActive;
	this->initialize();
}

VDGameObject::VDGameObject(const VDVector3& position,const VDQuaternion& rotation) : VDObject(){
	this->addComponet(VDTransform::createTransform());
	this->transform()->setPosition(position);
	this->transform()->setRotation(rotation);
	this->setName("GameObject");
	this->active = eActive;
	this->layer = VDLayer(0xFFFFFFFF);
	this->initialize();
}

void VDGameObject::initialize(bool serialize){
	if(serialize){
		gSerlizedGameObject.push_back(this);
	}
}	

VDGameObject::~VDGameObject(void){

} 

bool VDGameObject::operator==(VDGameObject* lh)const{
	return (this == lh);
}

bool VDGameObject::operator!=(VDGameObject* lh)const{
	return (this != lh);
}

VDGameObject& VDGameObject::operator=(const VDGameObject& object){
	VDObject::operator=(object);
	this->active = object.active;
	this->layer = object.getLayer();

	/*	copy component	TODO resolve this problem!	*/
	this->componets = object.componets;
	this->componets[0]->setGameObject(this);

	return *this;
}


VDAnimation* VDGameObject::animation(void)const{
	return this->getComponent<VDAnimation>();
}

VDCamera* VDGameObject::camera(void){
	return this->getComponent<VDCamera>();
}

VDRenderer* VDGameObject::renderer(void)const{
	return this->getComponent<VDRenderer>();
}

VDAudioSource* VDGameObject::audio(void)const{
	return this->getComponent<VDAudioSource>();
}

VDLight* VDGameObject::light(void)const{
	return this->getComponent<VDLight>();
}

VDRigidBody* VDGameObject::rigidBody(void)const{
	return this->getComponent<VDRigidBody>();
}

VDCollider* VDGameObject::collider(void)const{
	return this->getComponent<VDCollider>();
}

void VDGameObject::setActive(bool active){
	if(active == true && isActive())
		return;

	if(active){
		/*	decode if it was previously enabled	*/
		for(int x = 0; x < componets.size(); x++){
			if(componets[x]->getState() & (1 << 31) ){
				componets[x]->enable();
				componets[x]->setState( componets[x]->getState() & ~(1 << 31) );
			}
		}
		this->active |= VDGameObject::eActive;
	}
	else{
		/*	encode if component is enabled */
		for(int x = 0; x < this->componets.size(); x++){
			unsigned int state = componets[x]->getState();
			componets[x]->disable();
			componets[x]->setState( (state & ~0x1) | ( (state & VDBehavior::Enable) << 31) );
		}
		this->active = this->active & ~VDGameObject::eActive;
	}
}


void VDGameObject::setStatic(bool isStatic){

	bool wasStatic = this->isStatic();
	layer.setIndex(layer.getIndex() & ( isStatic == true ? ( (1 << 31) | layer.getIndex() )  : 0 ) );

	if(this->isStatic())
		VDScene::addstaticObject(this, wasStatic);
	else
		VDScene::removeStaticObject(this, wasStatic);
}

void VDGameObject::addComponet(VDBehavior* behavior){

	assert(behavior);

	behavior->setGameObject( this );
	this->componets.push_back(behavior);
	behavior->initializeComponent();

	if(this->isStatic()){

	}
}

void VDGameObject::removeComponent(VDBehavior* behavior){
	for(vector<VDBehavior*>::iterator x = this->componets.begin(); x != this->componets.end(); x++){
		if((*x) == behavior){
			(*x)->onDestroy();
			this->componets.erase(x);
			break;
		}
	}
	delete behavior;
}

VDBehavior* VDGameObject::detachComponent(VDBehavior* behavior){
	/*	is behavior part of the gameobject */
	VDBehavior* beh = NULL;
	for(vector<VDBehavior*>::iterator x = this->componets.begin(); x != this->componets.end(); x++){
		if((*x) == behavior){
			beh = (*x);
			this->componets.erase(x);
			(*x)->onDetach();
		}
	}
	return beh;
}

unsigned int VDGameObject::hasCustomBehavior(void)const{
	return (this->active & VDCustomBehavior::CustomBehavior);
}


void VDGameObject::destroy(void){
	VDGameObject::removeGameObject(this);
}

VDGameObject* VDGameObject::instantiate(VDGameObject* parent){
	unsigned int dataSize;
	unsigned int x;

	VDGameObject* rootInstance = VDGameObject::createGameObject();
	//*rootInstance = *this;

	memcpy(rootInstance->transform(), transform(),sizeof(VDTransform));
	rootInstance->transform()->setLocalPosition(transform()->getLocalPosition());
	rootInstance->transform()->setLocalRotation(transform()->getLocalRotation());
	if(!parent)
		rootInstance->transform()->setParent( NULL);
	else
		rootInstance->transform()->setParent( parent->transform() );

	/* create new component instance	*/
	for(x = 1; x < this->componets.size(); x++){
		// copy behavior data.
		VDBehavior* behaviorData = this->componets[x]->copyComponent(dataSize);
		// create new instance pointer
		rootInstance->componets.push_back((VDBehavior*)malloc(dataSize));
		// copy data of this Component with 
		memcpy(rootInstance->componets[x], behaviorData, dataSize);
		free(behaviorData);

		/*	copy virtual pointer	*/
		VD_COPY_VPTR(rootInstance->componets[x],this->componets[x]);


		rootInstance->componets[x]->setGameObject( rootInstance );
		rootInstance->componets[x]->instanceInitilize();

	}

	/*	fix child */
	//memcpy(rootInstance, this, sizeof(GameObject)  - sizeof(std::vector<Behavior*>));

	for(int x = 0; x < transform()->getChildCount(); x++ ){
		this->transform()->child(x)->gameObject()->instantiate(rootInstance);
	}
	return rootInstance;
}

VDGameObject* VDGameObject::instantiate(const VDVector3& position, const VDQuaternion& rotation){
	VDGameObject* rootInstance = instantiate();
	rootInstance->transform()->setPosition(position);
	rootInstance->transform()->setRotation(rotation);
	return rootInstance;
}

VDGameObject* VDGameObject::find(const char* name){
	VDGameObjectListIterator iterator = gSerlizedGameObject.begin();
	for(iterator = gSerlizedGameObject.begin(); iterator != gSerlizedGameObject.end(); iterator++){
		if(strcmp((*iterator)->getName(), name) == 0)
			return (VDGameObject*)(*iterator);
	}
	return NULL;
}

void VDGameObject::addGameObject(VDGameObject* g_Object){
	gSerlizedGameObject.push_back(g_Object);
}

void VDGameObject::removeGameObject(VDGameObject* g_Object){

	/*	remove all object parent to g_Object	*/
	for(unsigned int cx = 0; cx < g_Object->transform()->getChildCount(); cx++){
		VDGameObject::removeGameObject(g_Object->transform()->child(cx)->gameObject());

	}

	/*	remove all component connected to gameobject.	*/
	for(int x = g_Object->componets.size() - 1; x >= 0; x--){
		g_Object->componets[x]->onDestroy();
		/*	check who owns the data	*/
		//free(g_Object->componets[x]);
		g_Object->componets.pop_back();

	}

	/*	remove object from list	*/
	for(list<VDGameObject*>::iterator x = gSerlizedGameObject.begin(); x != gSerlizedGameObject.end(); x++){
		if(((VDGameObject*)*x) == g_Object){
			gSerlizedGameObject.erase(x);
			break;
		}
	}

	/*	TODO evaluate if gameobject should be deallocated here or not!	*/
	if(!VDScene::getScene()->gameobjects.isValidItem(*g_Object))
		free(g_Object);
	else
		VDScene::getScene()->gameobjects.Return(g_Object);
}

int VDGameObject::existComponet(const VDTypeInfo& info)const{
	for(int x = this->componets.size() -1; x >= 0; x--){
		if(*info.getType() == typeid(this->componets[x])){
			return 1;
		}
	}

	return 0;
}




// static void* private_TaskUpdate(VDTaskSchedule::VDTaskPackage* package){
// 	register VDGameObject* g = (VDGameObject*)package->begin;
// 	register VDGameObject* end = (VDGameObject*)package->end;
// 	while(g != package->end){
// 		if(!g->hasCustomBehavior())
// 			continue;

// 		for(int x = g->getComponentCount() - 1; x >= 0; x--){
// 			if(g->getComponentByIndex(x)->isCustomBehavior())
// 				VDCASTP(VDCustomBehavior*,g->getComponentByIndex(x))->update();

// 		}/*	update	*/

// 		if(!g->hasCustomBehavior())
// 			continue;

// 		for(int x = g->getComponentCount() - 1; x >= 0; --x){
// 			if(g->getComponentByIndex(x)->isCustomBehavior())
// 				VDCASTP(VDCustomBehavior*,g->getComponentByIndex(x))->lateUpdate();

// 		}/*	fixed update	*/

// 		g++;
// 	}
// 	return NULL;
// }


void VDGameObject::internalGameObjectUpdate(VDDoubleBufferedAllocator* allocator){

	/*
	int num = gSerlizedGameObject.size();
	list<VDGameObject*>::iterator begin;
	list<VDGameObject*>::iterator end;
	for(int x = 0; x < num; x += 16){
		//g = (*gIterators);
		VDTaskSchedule::VDTaskPackage package = {0};

		package.begin = &gSerlizedGameObject.begin();
		package.end = (void*)((gSerlizedGameObject.begin() + x ) +  ( (num - x) <= 16 ) ? num % 16 : num );
		package.callback = taskUpdate;
		VDEngine::getTaskSchedule().submitTask(&package);
	}
	*/

	register VDGameObject* g;
	VDGameObjectListIterator iterator;
	/*	TODO check if to use task schedule here as well.	*/
	for(iterator = gSerlizedGameObject.begin();
			iterator !=  gSerlizedGameObject.end();
			iterator++){

		g = (*iterator);

		if(!(*iterator)->hasCustomBehavior())
			continue;

		for(int x = g->componets.size() - 1; x >= 0; x--){
				if(g->componets[x]->isCustomBehavior())
				VDCASTP(VDCustomBehavior*,g->componets[x])->update();

		}/*	update	*/
	}

	for(iterator = gSerlizedGameObject.begin();
			iterator !=  gSerlizedGameObject.end();
			iterator++){
		g = (*iterator);

		if(!g->hasCustomBehavior())
			continue;

		for(int x = (*iterator)->componets.size() - 1; x >= 0; --x){
			if(g->componets[x]->isCustomBehavior())
				VDCASTP(VDCustomBehavior*,g->componets[x])->lateUpdate();

		}/*	fixed update	*/

	}/*	iterators	*/
}

void VDGameObject::internalGameObjectFixedUpdate(VDDoubleBufferedAllocator* allocator){
	register VDGameObject* g;
	list<VDGameObject*>::iterator mIterators = gSerlizedGameObject.begin();

	for(; mIterators !=  gSerlizedGameObject.end(); mIterators++){
		g = (*mIterators);

		if(!g)
			continue;

		if(!(*mIterators)->hasCustomBehavior())
			continue;


		for(int x = g->componets.size() - 1; x >= 0; x--){
			if(g->componets[x]->isCustomBehavior())
				VDCASTP(VDCustomBehavior*,g->componets[x])->fixedUpdate();

		}/*	fixed update	*/
	}

}

VDGameObject* VDGameObject::createPrimitive(VDGameObject::Primitive primitive, bool Collision, bool rigidbody){

	/**/
	VDGameObject* primitivObject = VDGameObject::createGameObject();
	primitivObject->addComponet<VDRenderer>();


	/**/
	VDMesh* mesh = NULL;
	switch(primitive){
	case eCube:
		mesh = VDGeometryProcedure::createCube(2.5f,0);
		if(Collision)
			primitivObject->addComponet<VDBoxCollider>();
		break;
	case eQuad:
		mesh = VDGeometryProcedure::createQuad(2,2,0, SDL_TRUE);
		if(Collision)
			primitivObject->addComponet<VDPlaneCollider>();
		break;
	case ePlane:
		mesh =  VDGeometryProcedure::createQuad(5,5,10, SDL_TRUE);
		if(Collision)
			primitivObject->addComponet<VDPlaneCollider>();
		break;
	case eGrid:
		mesh = VDGeometryProcedure::createGrid(10,10,1.0f, VDGeometryProcedure::normal);
		if(Collision)
			primitivObject->addComponet<VDPlaneCollider>();
		break;
	default:
		break;
	}// end switch Primitiv Desc

	/**/
	if(mesh == NULL){
		VDDebug::log("Primitive %d couldn't be created.\n", primitive);
	}else{
		primitivObject->getComponent<VDRenderer>()->setMesh( mesh );
	}

	return primitivObject;
}

VDGameObject* VDGameObject::createCameraController(void){
	VDGameObject* camerController = VDGameObject::createGameObject(); // create new GameObject .
	camerController->setName("Camera Controller");
	camerController->addComponet(new VDCameraController()); // new custom componets.
	return camerController;
}

VDGameObject* VDGameObject::createGameObject(void){
	VDGameObject* obj = VDScene::getScene()->gameobjects.obtain();
	memset(obj, NULL, sizeof(VDGameObject));

	/**/
	*obj = VDGameObject(SDL_FALSE);
	VDGameObject::addGameObject(obj);
	return obj;
}
