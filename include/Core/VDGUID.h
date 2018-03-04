/*
    Copyright (C) 2015  Valdemar Lindberg

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
#ifndef _VD_GUID_H_
#define _VD_GUID_H_
#include"../VDSystem.h"

/**
 *
 */
class VDDECLSPEC VDGUID{
public:	/*	*/

	inline VDGUID(void){}

	inline VDGUID(const VDGUID& uid){
		*this = uid;
	}

	inline explicit VDGUID(unsigned int uid){
		this->uid = uid;
	}

	/**
	 *
	 *	@Return
	 */
	inline unsigned int getGUID(void)const{
		return this->uid;
	}

	/**
	 *
	 *	@Return
	 */
	inline bool operator==(const VDGUID& gui)const{
		return ( gui.getGUID() == this->getGUID() );
	}

	/**
	 *
	 *	@Return
	 */
	inline bool operator>(const VDGUID& gui)const{
		return ( this->getGUID() > gui.getGUID() );
	}

	/**
	 *
	 *	@Return
	 */
	inline bool operator<(const VDGUID& gui)const{
		return ( this->getGUID() < gui.getGUID() );
	}


private:	/*	Attributes.	*/

	unsigned int uid;

public:	/*	getNextID.	*/

	/**
	 *
	 *	@Return
	 */
	static unsigned long long int VDAPIENTRY getNextID(void);

	/**
	 *
	 */
	static void VDAPIENTRY setNextID(unsigned long long int id);

	/**
	 *
	 */
	static unsigned long long int nextID;
	static int bitSize;
};




#endif
