/*
 *	VDEngine virtual dimension game engine.
 *	Copyright (C) 2014  Valdemar Lindberg
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _VD_ENGINE_H_
#define _VD_ENGINE_H_ 1
#include "../VDDef.h"
#include "../VDSimpleType.h"
#include "Rendering/VDRenderSetting.h"
#include "VDConfig.h"
#include <Core/Singleton.h>
#include <Core/VDEvent.h>
#include <FragCore.h>

namespace vdengine {
	/**
	 *	Sub system of the engine.
	 */
	enum SubSystem {
		None = 0x0,
		Debug = 0x4,
		Audio = 0x8,
		Rendering = 0x10,
		Physic = 0x1000,
		Initialize = 0x2000,

		Default = (Audio | Physic | Rendering | Initialize),
		All = 0xFFFFFFFF,
	};

	/**
	 *	Engine subroutine.
	 */
	enum class SubRoutine {
		Update = 0x1,		   /*	Update every frame.	*/
		FixedUpdate = 0x2,	   /*	Update with the same frequency intervale.	*/
		Render = 0x4,		   /*	In rendering pipeline.	*/
		ShadowRendering = 0x8, /*	In shadow rendering pipeline.	*/
		Culling = 0x10,		   /*	In culling routine.	*/
		GUI = 0x20,			   /*	In GUI rendering.	*/
	};

	/**
	 *	Engine class is responsible for
	 *	initilize all the component. Where the
	 *	init method must be called before using
	 *	the library.
	 */
	class VDDECLSPEC VDEngine : public fragcore::Singleton<VDEngine> {
	  public:
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
		static int VDAPIENTRY init(int argc, const char **argv, SubSystem subsystem = Default);

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
		static void VDAPIENTRY quit();

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
		static int VDAPIENTRY run();

		/**
		 *	Get engine subsystem.
		 *
		 *	@Return
		 */
		static SubSystem VDAPIFASTENTRY getSubSystem();

		static SceneManager *getSceneManager();

		/**
		 *	Get window assoicated with the game engine.
		 */
		static fragcore::RendererWindow *VDAPIENTRY getWindow();

		/**
		 *	Set window.
		 */
		static void VDAPIENTRY setWindow(fragcore::RendererWindow *window);

		/**
		 *	Set custom callback function.
		 */
		static void VDAPIENTRY addCallBack(SubRoutine enumCallBack, VDCustomCallBack callback);
		static void VDAPIENTRY addCallBack(SubRoutine enumCallBack, const std::vector<VDCustomCallBack> &callbacks);

		/**
		 *	Remove callback.
		 */
		static void VDAPIENTRY removeCallBack(SubRoutine enumCallBack, VDCallBack callback);
		static void VDAPIENTRY removeCallBack(SubRoutine enumCallBack, const std::vector<VDCustomCallBack> &callbacks);

		/**
		 * Get list of all callback of specified subroutine.
		 */
		static std::vector<VDCustomCallBack> &VDAPIENTRY getCallBack(SubRoutine routines);

		/**
		 * Get task scheduler associated with the engine.
		 */
		static fragcore::IScheduler &VDAPIENTRY getTaskSchedule();

		/**
		 * Get configuration object, used for defining the execution
		 * of the engine application.
		 */
		static fragcore::IConfig *VDAPIENTRY getConfig();

		/**
		 *	Get engine binary build version.
		 *
		 *	@Return	version.
		 */
		static unsigned int VDAPIENTRY getBuildVersion(unsigned int *major, unsigned int *minor,
													   unsigned int *revision);

		/**
		 *	Get version of the engine.
		 *	@Return non-null terminated string.
		 */
		static const char *VDAPIENTRY getVersion();

	  private: /*	Internal methods.	*/
		/**
		 *	read argument options.
		 */
		static int VDAPIENTRY readArgument(int argc, const char **argv, unsigned int pre);

	  private: /*	Private	Constructor.	*/
		/*
		 *	Flag
		 */
		unsigned int flag;
		SubSystem subsystems;
		fragcore::Ref<SceneManager> sceneManager;

		unsigned int active;

		// fragcore::PoolAllactor<SDL_GLContext> glcontext;
		fragcore::RendererWindow *window;

		unsigned int cursorVisible;

		// VDPhysicEngine physic;
		// VDHANDLE audioContext;
		fragcore::AudioInterface *audioContext;
		// VDEngineScene *scene;
		VDDebug *debug;
		VDRenderSetting renderSettings;

		/*
		 *	Task schedule for utilizing
		 *	n number of cores evenly.
		 */
		fragcore::IScheduler *schedule;
		/*
		 *	Custom callback routine.
		 */

		std::map<unsigned int, std::vector<VDCustomCallBack>> routines;
		std::vector<VDEvent *> events;

		fragcore::Capability *cap;
		fragcore::DeviceInfo *device;
		fragcore::Features *features;
		Ref<fragcore::IConfig> config;
		VDConfigure *config;

	  private:
		VDEngine() {}
		VDEngine(const VDEngine &other);
	};

} // namespace vdengine
#endif
