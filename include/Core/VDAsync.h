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
#ifndef _VD_ASYNC_H_
#define _VD_ASYNC_H_ 1
#include"../VDDef.h"

/**
 *
 */
typedef struct async_request_handle{
	FILE* file;		/*	*/
	char* path;		/*	*/
}VDAsyncRequestHandle;


/**
 *	For loading file asynchronous in
 *	background in separated threads and
 *	for callback for each fetched data block.
 */
class VDDECLSPEC VDASync{
public:

	/**
	 *	Synchronization callback mode.
	 */
	enum AsyncMode{
		eFull = 	0x1,		/*	Callback once fully loaded to memory.	*/
		eBlock = 	0x2,		/*	Block size interrupted.	*/
		eRead = 	0x4,		/*	*/
		eWrite = 	0x8,		/*	*/
	};

	VDASync(void);
	VDASync(const VDASync& sync);
	~VDASync(void);

private:	/*	Attributes.	*/

	FILE* file;		/*	*/

public:

	/**
	 *
	 */
	VDAsyncRequestHandle VDAPIENTRY open(const char* cfilename);


	/**
	 *	Close
	 */
	void VDAPIFASTENTRY close(VDAsyncRequestHandle* handle);

	/**
	 *
	 */
	void VDAPIENTRY readFile(VDAsyncRequestHandle* handle, void* buffer,
			int buflem, AsyncMode mode); //void (*VDAFileSyncCallBack)(void* pair, unsigned int reserved) );
	void VDAPIENTRY writeFile(VDAsyncRequestHandle* handle, void* buffer,
			int buflem, AsyncMode mode); // void (*VDAFileSyncCallBack)(void* pair, unsigned int reserved) );

	/**
	 *
	 */
	void VDAPIENTRY readFile(VDAsyncRequestHandle* handle, void* buffer,
			int buflem,
			void (*VDAFileSyncCallBack)(void* buffer, unsigned int buflen,
					AsyncMode mode), AsyncMode mode);
	void VDAPIENTRY writeFile(VDAsyncRequestHandle* handle, void* buffer,
			int buflem,
			void (*VDAFileSyncCallBack)(void* buffer, unsigned int buflen,
					AsyncMode mode), AsyncMode mode);

public:	/*	Static methods.	*/

	/**
	 *	Wait in till the file from handle
	 *	has finished of fetching all data.
	 */
	static int VDAPIENTRY wait(VDAsyncRequestHandle* handle);

};

#endif
