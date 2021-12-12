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
#ifndef _VD_CONTACT_H_
#define _VD_CONTACT_H_ 1
#include "VDCollider.h"

/**
 *
 */
class VDDECLSPEC VDContact{
public:
	VDContact();
	VDContact(const VDContact& contact);

	/**
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getCount() const;

	/**
	 *	@Return
	 */
	VDVector3 VDAPIENTRY impulse(int index)const;

	/**
	 *	@Return
	 */
	VDVector3 VDAPIENTRY point(int index)const;

	/**
	 *	@Return
	 */
	VDVector3 VDAPIENTRY normal(int index)const;

	/**
	 *	@Return
	 */
	float VDAPIENTRY distance(int index)const;


private:	/*	Attributes.	*/

	void* pcontact;		/*	*/
	unsigned int count;	/*	*/
};

#endif
