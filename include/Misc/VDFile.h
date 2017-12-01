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
#ifndef _VD_FILE_H_
#define _VD_FILE_H_ 1
#include"../VDDef.h"
#include<string.h>
#include<string>

/**
 *
 */
class VDDECLSPEC VDFile{
public:	/*	Static methods.	*/

	/**
	 *	Load file.
	 *
	 *	@Return number of bytes loaded from file.
	 */
	static long int VDAPIENTRY load(const char* cfilename, char** racBuffer);

	/**
	 *	Load file.
	 *
	 *	@Return number of bytes loaded from file.
	 */
	static long int VDAPIENTRY load(const char* cfilename, char** racBuffer, long int& riSize);

	/**
	 *	Load string from file.
	 *
	 *	@Return number of bytes loaded from file.
	 */
	static long int VDAPIENTRY loadString(const char* cfilename, char** racBuffer);


	/**
	 *
	 */
	static void VDAPIENTRY save(const char* cfilename, const char* racBuffer, long int riSize);

	/**
	 *
	 *
	 *	@Return
	 */
	static long int  VDAPIENTRY append(const char* cfilename, char* acBuffer, int riSize);

	/**
	 *	Get file size in bytes.
	 */
	static long int VDAPIENTRY size(const char* cfilename);

	/**
	 *	Open safe write pointer.
	 */
	static FILE* VDAPIENTRY safeOpenWrite(const char* cfilename);

	/**
	 *	Open safe write append pointer.
	 */
	static FILE* VDAPIENTRY safeOpenWriteAppend(const char* cfilename);

	/**
	 *	Open safe read pointer.
	 */
	static FILE* VDAPIENTRY safeOpenRead(const char* cfilename);

	/**
	 *	Perform save write.
	 */
	static void VDAPIENTRY safeWrite(FILE *f, const void* buffer, long int count);

	/**
	 *	Perform safe read.
	 */
	static void VDAPIENTRY safeRead(FILE*f, void* buffer, long int count);

	/**
	 *	Perform safe write.
	 */
	static void VDAPIENTRY safeWrite(FILE*f, void* buffer, long int offset, long int riSize);

	/**
	 *	Perform safe Read.
	 */
	static void VDAPIENTRY safeRead(FILE*f, void* buffer,long int offset, long int count);

	/**
	 *	Get directory from file path.
	 */
	static std::string getDirectory(const char* cpath);

	/**
	 *	@Return true if path is a relative path.
	 */
	static bool VDAPIENTRY isRelativePath(const char* cfilename);

	/**
	 *	@Return true if path is an absolute path.
	 */
	static bool VDAPIENTRY isAbsoultePath(const char* cfilename);

	/**
	 *	@Return true if file exits.
	 */
	static bool VDAPIENTRY existFile(const char* cfilename);

	/**
	 *	@Return true if directory.
	 */
	static bool VDAPIENTRY isDirectory(const char* cdirectory);

	/**
	 *	@Return number of directory exist in directory.
	 */
	static int VDAPIENTRY directoryCount(const char* cdirectory);

	/**
	 *	@Return get subdirectory in directory.
	 */
	static const char* VDAPIENTRY getSubDirectory(const char* cdirectory, int index);

	/**
	 *	Create directory.
	 *	@Return true if succesfully.
	 */
	static bool VDAPIENTRY createDirectory(const char* directory);

	/**
	 *	Remove directory by given directory.
	 */
	static void VDAPIENTRY removeDirectory(const char* directory);

};

#endif
