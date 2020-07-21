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
#ifndef _VD_GZFILE_H_
#define _VD_GZFILE_H_ 1
#include"../VDSystem.h"

/**
 *	Responsible for loading
 *	compressed gz files.
 */
class VDDECLSPEC VDGZFile{
public:	/*	Static methods.	*/


	/**
	 *	Load compressed file.
	 *
	 *	@Return number of uncompressed bytes.
	 */
	static long int VDAPIENTRY load(const char* cfilename, char** racBuffer);

	/**
	 *	Load compressed string. Adding a null
	 *	terminator at the end.
	 *
	 *	@Return length of the string.
	 */
	static long int VDAPIENTRY loadString(const char* cfilename, char** racBuffer);

};


#endif
