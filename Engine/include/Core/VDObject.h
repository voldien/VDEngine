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
#ifndef _VD_OBJECT_H_
#define _VD_OBJECT_H_ 1
#include"../VDDef.h"
#include"../Core/VDGUID.h"
#include<iostream>
#include<malloc.h>
#include<string.h>

/**
 *	Base object for all object intended
 *	to part of the game engine scene.
 *
 */
class VDDECLSPEC VDObject{
public:
	enum ObjectState{
		eNothing = 0x0,

		/**
		 *	Object has been modified.
		 */
		eModified = 0x1,

		/**
		 *	Object won't change.
		 *	It will prevent VDAssetObject from
		 *	releasing resources.
		 */
		eStatic = 0x2,
	};

	inline VDObject(void){
		this->mflag = 0;
		this->muiID = VDGUID::getNextID();
		this->mmame = NULL;
	}

	inline VDObject(const VDObject& obj){
		*this = obj;
	}

	inline ~VDObject(void){
		if(this->getName()){
			free(this->mmame);
		}
		this->mmame = NULL;
	}

	/**
	 *	Get object name.
	 *
	 *	@Return pointer to name.
	 */
	inline const char* getName(void)const{
		return this->mmame;
	}

	/**
	 *	Set object name.
	 */
	inline void setName(const char* name){
		if(!name)
			return;

		char* tmp = (char*)realloc(this->mmame, strlen(name) + 1);
		if(tmp){
			this->mmame = tmp;
			memcpy(this->mmame, name, strlen(name) + 1);
		}
	}

	/**
	 *	Get object flag state.
	 */
	inline unsigned int getFlag(void)const{
		return this->mflag;
	}

	/**
	 *	Set object's flag state .
	 */
	inline void setFlag(unsigned int flag){
		this->mflag = flag;
	}

	/**
	 *	Get object unique instance ID.
	 */
	inline unsigned int getInstanceID(void)const{
		return this->muiID;
	}

	/**
	 *	Set object instance ID.
	 */
	inline void setInstanceID(unsigned int muiID){
		this->muiID = muiID;
	}

	/**
	 *	Assign object.
	 */
	inline VDObject& operator=(const VDObject& obj){
		this->setName(obj.getName());
		this->setFlag(obj.getFlag());
		return *this;
	}

	/**
	 *	Display object informatin.
	 */
	friend std::ostream& operator<<(std::ostream& of, const VDObject& obj){
        of << "name : " << obj.getName() << "flag : " << obj.getFlag();
        return of;
	}

	/**
	 *	Get object to string.
	 */
	const char* toString(void)const{
		return this->mmame;
	}


protected:	/*	Attributes.	*/

	unsigned int mflag;
	unsigned int muiID;
	char* mmame;
};

#endif
