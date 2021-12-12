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
#ifndef _VD_TRANSFORM_H_
#define _VD_TRANSFORM_H_ 1
#include"../Core/VDBehavior.h"
#include"../VDSimpleType.h"

/**
 *	Transformation of node object.
 */
class VDDECLSPEC VDTransform : public VDBehavior {

	typedef struct vd_node_t {
		VDTransform* parent;
		VDTransform* sibling;
		VDTransform* child;
	}VDNode;

private:

	VDTransform();
	VDTransform(const VDTransform& transform);
	VDTransform(const VDVector3& position, const VDQuaternion& rotation, const VDVector3& scale); 
public:

	~VDTransform();

public:	/**/

	virtual void VDAPIENTRY initializeComponent();
	virtual void VDAPIENTRY onEnable() override;
	virtual void VDAPIENTRY onDisable() override;
	virtual void VDAPIENTRY onDestroy() override;
	virtual VDBehavior* VDAPIENTRY copyComponent(unsigned int& dataSize) override;

protected:	/*	Attributes.	*/

	/*	Node translation.	*/
	VDVector3 postion;			/*	*/
	VDVector3 scale;			/*	*/
	VDQuaternion rotation;		/*	*/
	/*	Node internal structure.	*/
	VDTransform* parent;		/*	*/
	VDTransform* sibling;		/*	*/
	VDTransform* mchild;		/*	*/
	/*	*/
	VDPhysicActor* base; // reference to VDPhysic Actor base
	unsigned int childCount;	/*	*/
	unsigned int flag;			/*	*/

public:	/*	Public methods.	*/
	
	VDTransform& operator=(const VDTransform& transform);

	/*
	 *	Get Heirical Root Node.
	 *	@Return
	 */
	VDTransform* VDAPIFASTENTRY root()const;

	/**
	 *	Rotate Transform Eular in Degree.
	 */
	void VDAPIENTRY rotate(const VDVector3& align);

	/**
	 *	Rotate Transform By Eular.
	 */
	void VDAPIENTRY rotate(float x, float y, float z);

	/**
	 *	Rotate Around a point.
	 */
	void VDAPIENTRY rotateAround(const VDVector3& align, const VDVector3& pivotPoint);

	/**
	 *	Rotate to look at transform node.
	 */
	void VDAPIENTRY lookAt(const VDTransform* transform);

	/**
	 *	Rotate to look at gameobject's transform node.
	 */
	void VDAPIENTRY lookAt(const VDGameObject* gameObject);

	/**
	 *	Rotate to look at world position.
	 */
	void VDAPIENTRY lookAt(const VDVector3& Target);

	/**
	 *	Translate the node.
	 */
	void VDAPIENTRY translate(float x, float y, float z);

	/**
	 *	Get number of children.
	 */
	int VDAPIFASTENTRY getChildCount()const;


	/**
	 *	Get child by index.
	 *	@Return
	 */
	VDTransform* VDAPIENTRY child(unsigned int index)const;

	/**
	 *	Find transform node by gameobject name.
	 */
	VDTransform* VDAPIENTRY findChild(const char* transformName);

	/**
	 *	Will iterate through all parent node.
	 */
	int VDAPIENTRY isChildOf(const VDTransform* parentTransform)const;

	/**
	 *	add child to transform hierical. child gets reference to parent which is this.
	 */
	void VDAPIENTRY addChild(VDTransform* childTransform);

	/**
	 *	Detach All Children from this transforms.
	 */
	void VDAPIFASTENTRY detachChildren();

	/**
	 *	Detach Transform from parent if found.
	 */
	void VDAPIENTRY detachChild(VDTransform* transform);

	/**
	 *	Detach child based on its child index
	 */
	void VDAPIENTRY detachChild(int index);

	/**
	 *	Detach child based on its name.
	 */
	void VDAPIENTRY detachChild(const char* name);

	/*Ä
	 *	Remove Parent from this Transform.
	 */
	void VDAPIENTRY removeParent();

	/**
	 *
	 */
	void VDAPIENTRY setParent(VDTransform* parent);

	/**
	 *
	 */
	VDTransform* VDAPIFASTENTRY getParent()const;

	/**
	 *	Get Node TransformationDirection Based On Direction
	 *	@Return
	 */
	VDVector3 VDAPIENTRY transformDirection(const VDVector3& direction)const;

	/**
	 *
	 */
	VDVector3 VDAPIENTRY transformDirection(float x,float y,float z)const;

	/**
	 *	Get Node Inversed TransformationDirection Based On Direction
	 *	@Return
	 */
	VDVector3 VDAPIENTRY inverseTransformDirection(const VDVector3& direction)const;

	/**
	 *
	 *	@Return
	 */
	inline VDVector3 VDAPIENTRY inverseTransformDirection(float x,float y,float z)const;

	/**
	 *
	 */
	void VDAPIENTRY setPosition(const VDVector3& position);

	/**
	 *
	 */
	void VDAPIENTRY setScale(const VDVector3& scale);

	/**
	 *
	 */
	void VDAPIENTRY setRotation(const VDQuaternion& rotation);

	/**
	 *	Get global position.
	 */
	VDVector3 VDAPIENTRY getPosition()const;

	/**
	 *	Get global scale.
	 */
	VDVector3 VDAPIENTRY getScale()const;

	/**
	 *	Get global rotation.
	 */
	VDQuaternion VDAPIENTRY getRotation()const;

	/**
	 *
	 */
	void VDAPIENTRY setLocalPosition(const VDVector3& position);

	/*
	 *	change a bit. becuae a local rotation shouldn't apply translation on the node. only child node
	 */
	void VDAPIENTRY setLocalRotation(const VDQuaternion& rotation);

	/**
	 *
	 */
	void VDAPIENTRY setLocalScale(const VDVector3& scale);

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY getLocalPosition()const;

	/**
	 *
	 *	@Return
	 */
	VDQuaternion VDAPIFASTENTRY getLocalRotation()const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY getLocalScale()const;

	/**
	 *	Transformation Matrix of worldSpace
	 *	@Return
	 */
	//VDMatrix4x4 VDAPIFASTENTRY getMatrix()const;

	/*
	 *	Tranformation Matrix related to parent transformation Matrix
	 *	@Return
	 */
	//VDMatrix4x4 VDAPIFASTENTRY getLocalMatrix()const;

	/**
	 *	Get View Matrix.
	 *	@Return
	 */
	VDMatrix4x4 VDAPIFASTENTRY getViewMatrix()const;

	/**
	 *
	 *	@Return
	 */
	VDMatrix4x4 VDAPIFASTENTRY getLocalViewMatrix()const;

	/**/
	void VDAPIENTRY SetLocalRotationTransformation(const VDQuaternion& setRotation, const VDVector3& unitDelta);

	/**/
	void VDAPIENTRY SetLocalDeltaPos(const VDVector3& deltaMotion);

	/**/
	void VDAPIENTRY SetRigidBodyPosition(const VDVector3& rigidbodyPosition);

	/**/
	void VDAPIENTRY SetRigidBodyRotation(const VDQuaternion& rigidbodyPosition);


	//Animation Connection for the hierarchical transformation 
	void inline AnimationSetPositionX( float x){
		this->setLocalPosition(VDVector3(x,this->postion.y(),this->postion.z()));
	}
	void inline AnimationSetPositionY( float y){
		this->setLocalPosition(VDVector3(this->postion.x(),y,this->postion.z()));
	}
	void inline AnimationSetPositionZ( float z){
		this->setLocalPosition(VDVector3(this->postion.x(),this->postion.y(),z));
	}
	void inline animationSetRotationX( float x){
		this->setRotation(VDQuaternion(x,this->rotation.getYaw(),this->rotation.getRoll()));
	}
	void inline AnimationSetRotationY( float y){
		this->setRotation(VDQuaternion(this->rotation.getPitch(),y,this->rotation.getRoll()));
	}
	void inline AnimationSetRotationZ( float z){
		this->setRotation(VDQuaternion(this->rotation.getPitch(),this->rotation.getYaw(),z));
	}

	void inline AnimationSetRotationQX(float x){
		this->setLocalRotation(VDQuaternion(x,this->rotation.y(),this->rotation.z(),this->rotation.w()));
	}
	void inline AnimationSetRotationQY(float y){this->setLocalRotation(VDQuaternion(this->rotation.x(),y,this->rotation.z(),this->rotation.w()));}
	void inline AnimationSetRotationQZ(float z){this->setLocalRotation(VDQuaternion(this->rotation.x(),this->rotation.y(),z,this->rotation.w()));}
	void inline AnimationSetRotationQW(float w){this->setLocalRotation(VDQuaternion(this->rotation.x(),this->rotation.y(),this->rotation.z(),w));}

	void inline AnimationSetScaleX(float x){
		this->setLocalScale(VDVector3(x,this->scale.y(), this->scale.z()));
	}
	void inline AnimationSetScaleY(float y){
		this->setLocalScale(VDVector3(this->scale.x(),y, this->scale.z()));
	}
	void inline AnimationSetScaleZ(float z){
		this->setLocalScale(VDVector3(this->scale.x(), this->scale.y(),z));
	}

public:	/*	Creator function.	*/

	/**
	 *	Factory method for creating transform node.
	 *	@Return non-null transform object.
	 */
	static VDTransform* VDAPIENTRY createTransform();

};

#endif
