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
#ifndef _VD_PHYSICAL_MATERIAL_H_
#define _VD_PHYSICAL_MATERIAL_H_ 1
#include"../VDSystem.h"

/**
 *
 */
class VDDECLSPEC VDPhysicMaterial {
public:
	enum MaterialTemplate{
		eUnknown,
		eDefault,
		eCharacterController,
		eIce,
		eWood,
		eStone,
	};

	VDPhysicMaterial(void);
	VDPhysicMaterial(const VDPhysicMaterial& material);


	/**
	 *
	 */
	float VDAPIENTRY getStaticFriction(void);
	void VDAPIENTRY setStaticFriction(float staticfriction);

	/**
	 *
	 */
	float VDAPIENTRY getDynamicFriction(void);
	void VDAPIENTRY setDynamicFriction(float dynamicfriction);

	/**
	 *
	 */
	float VDAPIENTRY getBounciness(void);
	void VDAPIENTRY setBounciness(float bounciness);

	/*
	 *
	 */
	void setProperties(float staticFriction,
		float dynamicFriction,
		float restriction);

	/*
	 *
	 */
	void VDAPIENTRY enableFriction(void);

	/*
	 *
	 */
	void VDAPIENTRY disableFriction(void);

	/**/
	void* VDAPIENTRY  getMaterial(void)const{
		return this->m_material;
	}


	void VDAPIENTRY setMaterial(void* data){
		this->m_material = data;
	}

private:	/*	Attributes.	*/
	void* m_material;

	static int VDAPIFASTENTRY getCollectionSize(void);
};


#endif
