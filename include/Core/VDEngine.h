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
#ifndef _VD_ENGINE_H_
#define _VD_ENGINE_H_ 1
#include "VDConfig.h"
#include "../DataStructure/VDVector.h"
#include "../VDDef.h"
#include "../VDSimpleType.h"

/**
 *	Engine class is responsible for
 *	initilize all the component. Where the
 *	init method must be called before using
 *	the library.
 */
class VDDECLSPEC VDEngine{
public:

	/**
	 *	Sub system of the engine.
	 */
	enum SubSystem{
		eNone 				= 0x0,
		eDebug 				= 0x4,
		eAudio 				= 0x8,
		eDefualtMaterialLowQuality 	= 0x200,
		eDefualtMaterialHighQuality 	= 0x400,
		ePhysic 			= 0x1000,
		eInitialize 			= 0x2000,

		eDefault = ( eDefualtMaterialLowQuality | ePhysic ),
		eAll = (eDebug | eDefualtMaterialLowQuality | eDefualtMaterialHighQuality |
				ePhysic | eInitialize | eDefault)
	};

	/**
	 *	Engine subroutine.
	 */
	enum SubRoutine{
		eUpdate 		= 0x1,	/*	Update every frame.	*/
		eFixedUpdate		= 0x2,	/*	Update with the same frequency intervale.	*/
		eRendering		= 0x4,	/*	In rendering pipeline.	*/
		eShadowRendering	= 0x8,	/*	In shadow rendering pipeline.	*/
		eCulling		= 0x10,	/*	In culling routine.	*/
		eGUI			= 0x20,	/*	In GUI rendering.	*/
	};

	/**
	 *	Initialize the engine.
	 *
	 *	\argc
	 *
	 *	\argv
	 *
	 *	\subsystem
	 *
	 *	@Return
	 */
	static int VDAPIENTRY init(int argc, const char** argv, SubSystem subsystem = VDEngine::eDefault);

	/**
	 *	Initialize subsystem.
	 *
	 *	\subsystem
	 *
	 *	@Return
	 */
	static int VDAPIENTRY initSubSystem(SubSystem subsystem);


	/**
	 *	Release all resource associated with the engine.
	 */
	static void VDAPIENTRY releaseEngine(void);


	/**
	 *	Release subsystem resources.
	 *
	 *	@Return non-zero if successfully.
	 */
	static int VDAPIENTRY releaseSubSystem(SubSystem subsystem);

	/**
	 *	Start main engine loop.
	 *
	 *	@Return exit status.
	 */
	static int VDAPIENTRY run(void);

	/**
	 *
	 *	@Return
	 */
	static unsigned int VDAPIENTRY getFlag(void);

	/**
	 *	Get engine subsystem.
	 *
	 *	@Return
	 */
	static SubSystem VDAPIFASTENTRY getSubSystemFlag(void);


	/**
	 *	Get window assoicated with the game engine.
	 */
	static VDWindow* VDAPIENTRY getWindow(void);

	/**
	 * Get drawable window assoicated with the engine.
	 */
	static VDWindow* VDAPIENTRY getDrawable(void);

	/**
	 *	Set window.
	 */
	static void VDAPIENTRY setWindow(VDWindow* window);

	/**
	 *	Set drawable window.
	 */
	static void VDAPIENTRY setDrawable(VDWindow* window);

	/**
	 *	Set window title.
	 */
	static void VDAPIENTRY setWindowTitle(const char* title);

	/**
	 *	Get widnow title.
	 *	@Return non-null terminated string.
	 */
	static char* VDAPIENTRY getWindowTitle(void);

	/**
	 *	Bind OpenGL context to current thread.
	 */
	static void VDAPIENTRY bindOpenGLContext(const VDGLContext glContext);

	/**
	 *	Get main OpenGL context.
	 *	@Return non-null context pointer.
	 */
	static VDGLContext VDAPIENTRY getOpenGLContext(void);


	/**
	 *	Query a new shared instance of OpenGL context.
	 *
	 *	@Return non-null if succesfully creating a shared context.
	 */
	static VDGLContext* VDAPIENTRY querySharedOpenGLContext(void);

	/**
	 *	Release shared context and return pointer to the pool.
	 */
	static void VDAPIENTRY returnOpenGLContext(VDGLContext* context);

	/**
	 *	Set custom callback function.
	 */
	static void VDAPIENTRY setCallBack(SubRoutine enumCallBack, VDCustomCallBack callback);

	/**
	 *	Remove callback.
	 */
	static void VDAPIENTRY removeCallBack(SubRoutine enumCallBack, VDCallBack callback);

	/**
	 * Get list of all callback of specified subroutine.
	 */
	static VDVector<VDCustomCallBack>& VDAPIENTRY getCallBack(SubRoutine enumCallBack);

	/**
	 * Get task scheduler associated with the engine.
	 */
	static VDTaskSchedule& VDAPIENTRY getTaskSchedule(void);

	/**
	 * Get debug object.
	 */
	static VDDebug* VDAPIFASTENTRY getDebug(void);

	/**
	 * Get configuration object, used for defining the execution
	 * of the engine application.
	 */
	static VDConfigure::VDConfig* VDAPIENTRY getConfig(void);

	/**
	 *	Get engine binary build version.
	 *
	 *	@Return	version.
	 */
	static unsigned int VDAPIENTRY getBuildVersion(unsigned int* major, unsigned int* minor, unsigned int* revision);

	/**
	 *	Get version of the engine.
	 *	@Return non-null terminated string.
	 */
	static const char* VDAPIENTRY getVersion(void);

private:	/*	Internal methods.	*/

	/**
	 *	read argument options.
	 */
	static int VDAPIENTRY readArgument(int argc, const char** argv, unsigned int pre);

private:	/*	Private	Constructor.	*/

	VDEngine(void){}
};

#endif
