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
#ifndef _VD_LAYER_H_
#define _VD_LAYER_H_ 1
#include"../VDSystem.h"

/**
 *	Rendering layer.
 */
class VDDECLSPEC VDLayer {
public:

	VDLayer(void);
	VDLayer(const VDLayer& layer);
	explicit VDLayer(unsigned int index);

	/**
	 *	Get layer index.
	 */
	unsigned int VDAPIENTRY getIndex(void)const;

	/**
	 *	Set layer index.
	 */
	void VDAPIENTRY setIndex(unsigned int index);

	/**
	 *	Offset index.
	 */
	VDLayer& operator<<(int i);

	/**
	 *	Offset index.
	 */
	VDLayer& operator>>(int i);

	/**
	 *	@Return
	 */
	VDLayer operator&(const VDLayer& layer)const;

	/**
	 *	@Return
	 */
	unsigned int operator!(void)const;

	/**
	 *	@Return
	 */
	bool operator==(const VDLayer& layer)const;

	/**
	 *	@Return
	 */
	bool operator!=(const VDLayer& layer)const;

private:	/*	Attributes.	*/

	unsigned int index;	/*	Layer index.	*/

public:

	/**
	 *	Map layer index to string.
	 */
	static void VDAPIENTRY setIndextName(unsigned int index, const char* cname);

	/**
	 *	@Return get non null terminated string.
	 */
	static const char* VDAPIENTRY getIndexName(unsigned int index);

	/**
	 *	@Return get valid layer if succesfully.
	 */
	static VDLayer VDAPIENTRY getIndexByName(const char* cname);


private:	/*	Static attributes.	*/

	static char name[sizeof(index) * 8][32];
};

#endif
