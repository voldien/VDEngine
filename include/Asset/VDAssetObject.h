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
#ifndef _VD_ASSET_OBJECT_H_
#define _VD_ASSET_OBJECT_H_ 1
#include"VDSmartReference.h"
#include"Core/VDObject.h"

/**
 *	Asset object.
 *	Responsible for releasing resources
 *	when no reference to this object.
 */
class VDDECLSPEC VDAssetObject :  public VDObject{
public:
	VDAssetObject(void);
	VDAssetObject(const VDAssetObject& assetObject);
	virtual ~VDAssetObject(void);

	/**
	 *	Release objects resources.
	 */
	virtual void VDAPIENTRY release(void);

	/**
	 *	increment reference count.
	 */
	void VDAPIFASTENTRY increment(void);

	/**
	 *	decrement reference count.
	 */
	void VDAPIFASTENTRY deincrement(void);

	/**
	 *	Check if object should be exist.
	 *
	 *	@Return true if valid object.
	 */
	bool VDAPIENTRY isValid(void);

	/**
	 *	Assign object.
	 */
	VDAssetObject& operator=(const VDAssetObject& object);

protected:	/*	Attributes.	*/

	/**
	 *	Get reference object.
	 */
	VDSmartReference& getReference(void){
		return this->reference;
	}

	/**
	 *	Get read only smart reference.
	 */
	const VDSmartReference& getReference(void)const{
		return this->reference;
	}

	/**
	 *	Set reference objecft.
	 */
	void setReference(const VDSmartReference& reference){
		this->reference = reference;
	}

protected:	/*	Attributes.	*/

	/*
	 *
	 */
	VDSmartReference reference;
};

#endif
