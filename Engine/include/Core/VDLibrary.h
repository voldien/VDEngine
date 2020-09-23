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
#ifndef _VD_LIBRARY_H_
#define _VD_LIBRARY_H_ 1
#include"../VDSystem.h"

/**
 *	Loading external library in
 *	runetime.
 */
class VDDECLSPEC VDLibrary{
public:
	VDLibrary(void);
	VDLibrary(const char* clibrary);
	VDLibrary(const VDLibrary& library);
	~VDLibrary(void);

	/**
	 *	Open
	 *
	 *	@Return
	 */
	bool VDAPIENTRY open(const char* clibrary);

	/**
	 *	Close
	 *
	 *	@Return
	 */
	void VDAPIENTRY close(void);

	/**
	 *
	 *
	 *	@Return
	 */
	void* VDAPIENTRY getfunc(const char* pProcName);

private:	/*	Attributes.	*/

	void* mlib;
};

#endif
