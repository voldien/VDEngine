/*
	VDEngine virtual dimension game engine.
	Copyright (C) 2014  Valdemar Lindberg

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _VD_GAMEOBJECT_H_
#define _VD_GAMEOBJECT_H_ 1
#include "../Core/VDBehavior.h"
#include "../Core/VDLayer.h"

/*
 *
 */
typedef std::list<VDGameObject *> VDGameObjectList;
typedef std::list<VDGameObject *>::iterator VDGameObjectListIterator;
typedef std::vector<VDBehavior *> VDGameObjectComponent;
typedef std::vector<VDBehavior *>::iterator VDGameObjectComponentIterator;

/**
 *
 */
extern VDDECLSPEC VDGameObjectList gSerlizedGameObject; /*	GameObject List Of Game Level.	*/
// extern VDDECLSPEC fragcore::PoolAllactor<VDBehavior> gComponents;

/**
 *
 */
class VDDECLSPEC VDGameObject : public VDObject {
	friend class VDCustomBehavior;
	friend class VDComponent;
	friend class VDBehavior;

  public:
	/**
	 *
	 */
	enum ActiveState {
		/*is GameObject Active*/
		eActive = 0x1,
		/*Gameobject have a component of BroodBehavior as float*/
		eBroodBehavior = 0x2,
		/*Gameobject have a animation attached*/
		eAnimation = 0x4,
		/*GameObject have a  Rigidbody*/
		eRigidbody = 0x8,
	};

	/*
	 *
	 */
	enum Primitive {
		eCube = 0x1,
		eQuad = 0x2,
		ePlane = 0x3,
		eGrid,
	};

  private: /*	Use factory function createGameObject.	*/
	/**
	 *	Crate a Instance of GameObject. GameObject will be Serilized
	 *	to GameFrameWork.
	 *
	 *	[Note] Delete only object by using destroy. Don't use Delete
	 *	by own hand. can cause confligt with the application.
	 */
	VDGameObject(int serizlized = 1);
	VDGameObject(const VDGameObject &object);
	VDGameObject(const char *cName);
	VDGameObject(const VDVector3 &position, const VDQuaternion &rotation);

  public:
	~VDGameObject();

  private:								 /*	Attributes.	*/
	unsigned int active;				 /*	GameObject Active.	*/
	VDLayer layer;						 /*	*/
	std::vector<VDBehavior *> componets; /*	Pointer to conncted componets with the gameObject.	*/

  public:
	/**
	 *	Initialize GameObject. Important!
	 */
	void VDAPIFASTENTRY initialize(bool serialize = true);

	/**
	 *
	 */
	bool operator==(VDGameObject *lh) const;
	bool operator!=(VDGameObject *lh) const;
	VDGameObject &operator=(const VDGameObject &object);

	/**
	 *	Get predefined component
	 */
	VDAnimation *VDAPIFASTENTRY animation() const;
	inline VDTransform *transform() const { return VDCASTP(VDTransform *, this->componets[0]); }
	VDCamera *VDAPIFASTENTRY camera();
	VDRenderer *VDAPIFASTENTRY renderer() const;
	inline VDGameObject *gameObject() const { return (VDGameObject *)this; }
	VDAudioSource *VDAPIFASTENTRY audio() const;
	VDLight *VDAPIFASTENTRY light() const;
	VDRigidBody *VDAPIFASTENTRY rigidBody() const;
	VDCollider *VDAPIFASTENTRY collider() const;

	/**
	 *	Check if gameObject is active.
	 */
	inline bool isActive() const { return (this->active & eActive) != 0; }

	/**
	 *
	 */
	void VDAPIENTRY setActive(bool active);

	/**
	 *
	 */
	inline unsigned int getActiveFlag() const { return this->active; }
	/**
	 *
	 */
	inline void setActiveFlag(unsigned int flag) { this->active = flag; }

	inline void setLayer(const VDLayer &layer) { this->layer = layer; }

	inline VDLayer getLayer() const { return this->layer; }

	/**
	 *	@Return
	 */
	inline bool isStatic() const { return (layer.getIndex() & (1 << 31)) != 0 ? true : false; }

	/**
	 *
	 */
	void VDAPIFASTENTRY setStatic(bool _isStatic);

  protected:
	/**
	 *	@Return gameobject's component collection.
	 */
	inline std::vector<VDBehavior *> getComponentCollection() const { return this->componets; }

  public:
	inline int getComponentCount() const { return this->getComponentCollection().size(); }

	inline VDBehavior *getComponentByIndex(int index) const { return this->getComponentCollection()[index]; }

	/**
	 *	Get Component Attached to GameObject of Type.
	 *	[Return] return value nullptr indicate that there is no
	 *	Component of Type.
	 *	@Return
	 */
	template <class T> T *getComponent() const {
		for (int x = componets.size() - 1; x >= 0; x--) {
			if (typeid(*this->componets[x]) == typeid(T))
				return dynamic_cast<T *>(this->componets[x]);
		}
		for (int x = componets.size() - 1; x >= 0; x--) {
			if (typeid(VDBehavior).before(typeid(*this->componets[x])) >= 1)
				return dynamic_cast<T *>(this->componets[x]);
		}
		return nullptr;
	}

	/**
	 *
	 *	@Return
	 */
	template <class T> std::vector<T *> getComponents() {
		std::vector<T *> com(fragcore::SystemInfo::getPageSize());
		std::vector<T *> tmp;
		T *comp;
		int x;

		for (x = 0; x < transform()->getChildCount(); x++) {
			comp = transform()->child(x)->gameObject()->getComponents<T>();
			com.merge(tmp);
		}

		return com;
	}

	/**
	 *	Add Component to GameObject.
	 *  Classes Derivite from Behavior & BroodBehavior.
	 *  BroodBehavior Customs Script Component.
	 */
	void VDAPIENTRY addComponet(VDBehavior *behavior);

	/**
	 *	Add Component of Type. addComponet(Behavior* behavior);
	 *	Get Called Afterward and initlize the Component with gameobject
	 *
	 *	@Return
	 */
	template <class T> T *addComponet() {
		T *c_o = new T();
		this->addComponet(c_o);
		return c_o;
	}

	/**
	 *	Remove component by it's type.
	 */
	template <class T> void removeComponent() {
		for (unsigned int x = this->componets.size() - 1; x >= 0; x--) {
			if (typeid(*this->componets[x]) == typeid(T)) {
				this->removeComponent(this->componets[x]);
				break;
			}
		}
	}

	/*
	 *	Remove component
	 */
	void VDAPIENTRY removeComponent(VDBehavior *behavior);

	/**
	 *	@Return
	 */
	VDBehavior *VDAPIENTRY detachComponent(VDBehavior *behavior);

	/**
	 *	Check if Componet alredy of Type is Part of Current GameObject!
	 */
	int VDAPIENTRY existComponet(const VDTypeInfo &info) const;

	/**
	 *
	 */
	template <class T> int existComponentType() {
		for (int x = this->gameObject()->componets.size() - 1; x >= 0; x--) {
			if (typeid(*this->gameObject()->componets[x]) == typeid(T) ||
				typeid(*this->gameObject()->componets[x]).before(typeid(T)))
				return 1;
		}
		return 0;
	}

	/**
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY hasCustomBehavior() const;

	/*
	 *	Destroy this GameObject. all children of this parent will
	 *  be Destroyed as well.
	 */
	void VDAPIFASTENTRY destroy();

	/*
	 *	Create a instance of the gameObject as a copy with same properties.
	 *	@Return
	 */
	VDGameObject *VDAPIENTRY instantiate(VDGameObject *parent = nullptr);

	/*
	 *
	 *	@Return
	 */
	VDGameObject *VDAPIENTRY instantiate(const VDVector3 &position, const VDQuaternion &rotation);

  public: /*	Static methods.	*/
	/**
	 *	Add A GameObject to Game Level
	 */
	static void VDAPIFASTENTRY addGameObject(VDGameObject *object);

	/**
	 *	Remove a GameObject From Game Level.
	 */
	static void VDAPIENTRY removeGameObject(VDGameObject *object);

	/**
	 *	find GameObject By Given Name. If Return value equl to Zero
	 *	Then it means there wasn't any GameObject By The Give
	 *	Name. A bit expansive Executing Method.
	 *	Allocation GameObject is more Recommend.
	 *	@Return
	 */
	static VDGameObject *VDAPIENTRY find(const char *cname);

	/**
	 *	Find GameObject By Given Class Type. The First GameObject
	 *	With the Specified Class Type Will be Returned.
	 *	@Return
	 */
	template <typename T> static VDGameObject *findObjectByType() {
		VDGameObjectListIterator iterator;
		for (iterator = gSerlizedGameObject.begin(); iterator != gSerlizedGameObject.end(); iterator++) {
			for (int x = (*iterator)->componets.size() - 1; x >= 0; x--) {
				if (typeid((*iterator)->componets[x]) == typeid(T)) {
					return (VDGameObject *)(*iterator);
				}
			}
		}
		return nullptr;
	}

	/**
	 *	Find GameObjects By Given Class Type. All GameObjects
	 *	With Componet of Specified Class Type be Returned as
	 *	Vector of GameObject.
	 *	@Return
	 */
	template <class T> static std::vector<VDGameObject *> findObjectsByType() {
		std::vector<VDGameObject *> typeObject;
		VDGameObjectListIterator iterator;
		for (iterator = gSerlizedGameObject.begin(); iterator != gSerlizedGameObject.end(); iterator++) {
			for (int x = (*iterator)->componets.size() - 1; x >= 0; x--) {
				if (typeid((*iterator)->componets[x]) == typeid(T)) {
					typeObject.push_back((*iterator));
					break;
				}
			}
		}
		return typeObject;
	}

	/**
	 *	update all GameObjects update Methods!
	 */
	static void VDAPIENTRY internalGameObjectUpdate(VDDoubleBufferedAllocator *allocator = nullptr);

	/**
	 *
	 */
	static void VDAPIENTRY internalGameObjectFixedUpdate(VDDoubleBufferedAllocator *allocator);

	/**
	 *	@Return
	 */
	static VDGameObject *VDAPIENTRY createPrimitive(VDGameObject::Primitive primitive, bool collision = true,
													bool rigidbody = true);

	/**
	 *	@Return
	 */
	static VDGameObject *VDAPIENTRY createCameraController();

	/**
	 *	@Return
	 */
	static VDGameObject *VDAPIENTRY createGameObject();
};

#endif
