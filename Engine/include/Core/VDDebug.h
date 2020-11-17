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
#ifndef _VD_DEBUG_H_
#define _VD_DEBUG_H_ 1
#include"../VDSystem.h"
#include"../DataStructure/VDDataStructure.h"

/**
 *	Debug class, responsible for
 *	providing debugging information
 *	about the excecution of the program.
 */
class VDDECLSPEC VDDebug : fragcore::Singleton<VDDebug>{
public:

	VDDebug(void);
	VDDebug(const VDDebug& debug);
	~VDDebug(void);

	/**
	 *
	 */
	void VDAPIENTRY init(void);

	/**
	 *
	 */
	void VDAPIENTRY release(void);


private:	/*	Attributes.	*/

	vector<VDToolBase*> tools;	/*	*/
	int query[10];					/*	*/
	unsigned int mode;				/*	*/

public:	/*	*/

	/**
	 *	Get tools.
	 */
	vector<VDToolBase*>& VDAPIENTRY getTools(void){
		return this->tools;
	}

	/**
	 *	opengl query.
	 */
	void VDAPIENTRY begin(void);

	/**
	 *	opengl query.
	 */
	void VDAPIENTRY end(void);


	/**
	 *
	 */
	void VDAPIENTRY draw(VDCamera* camera = NULL);

	/**
	 *
	 */
	static void VDAPIENTRY viewPortDebugMode(unsigned int mode);

public: /*	Static methods.	*/

	/**
	 *	Is current application a debug build.
	 *
	 *	@Return true if a debug build.
	 */
	static bool VDAPIFASTENTRY isDebugBuild(void);

	/**
	 *	Return true if engine debug flag is set.
	 *
	 *	@Return true if debug is enabled.
	 */
	static bool VDAPIFASTENTRY isDebugEnabled(void);

	/**
	 *	Write to log output.
	 */
	static void VDAPIENTRY log(const char* format,...);

	/**
	 *	Write to log error output.
	 */
	static void VDAPIENTRY errorLog(const char* format,...);

	/**
	 *
	 */
	static void VDAPIENTRY warningLog(const char* format,...);

	/**
	 *
	 */
	static void VDAPIENTRY criticalLog(const char* format,...);

	/**
	 *
	 */
	static void VDAPIENTRY debugLog(const char* format, ...);

};

#endif
