/**
	VDEngine virtual dimension
    Copyright (C) 2017  Valdemar Lindberg


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
#ifndef _VD_ENGINE_CORE_H_
#define _VD_ENGINE_CORE_H_ 1

#include <Core/VDConfig.h>
#include <Core/VDEvent.h>
#include <DataStructure/VDPoolAllactor.h>
#include <DataStructure/VDVector.h>
#include <Physic/VDPhysic.h>
#include <Rendering/VDRenderSetting.h>
#include <Rendering/VDShader.h>
#include <Scene/VDScene.h>
#include <SDL2/SDL_video.h>
#include <VDDef.h>
#include <VDPrerequisites.h>
#include <VDSimpleType.h>
#include <VDSystemInfo.h>
#include <cstdio>
#include <map>

/**
 *	Internal engine core state.
 */
typedef struct vd_engine_core_t {


	/*
	 *	Flag
	 */
	unsigned int flag;

	unsigned int active;
	VDGLContext glc;
	VDPoolAllactor<SDL_GLContext> glcontext;
	VDWindow* window;
	VDWindow* drawable;
	unsigned int fullscreen;
	unsigned int cursorVisible;
	unsigned long int OpenGLEngineState;
	VDPhysicEngine physic;
	VDHANDLE audioContext;
	VDEngineScene* scene;
	VDDebug* debug;
	VDRenderSetting renderSettings;

	/*
	 *	Task schedule for utilizing
	 *	n number of cores evenly.
	 */
	//VDTaskSchedule schedule;

	/**
	 *
	 */
	FILE* log;

	/*
	 *	Custom callback routine.
	 */
	map<unsigned int, VDVector<VDCustomCallBack> > routines;

	VDVector<VDEvent*> events;

	/*	cached support	*/
	VDSystemInfo::VDCompatibility* compadability;

	/**
	 *
	 */
	VDConfigure::VDConfig* config;

} VDEngineCore;

extern VDDECLSPEC VDEngineCore engine;

#endif
