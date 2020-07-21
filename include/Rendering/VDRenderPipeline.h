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
#ifndef _VD_RENDER_PIPELINE_H_
#define _VD_RENDER_PIPELINE_H_ 1
#include <Core/VDTaskSchedule.h>
#include <DataStructure/VDQueue.h>
#include <DataStructure/VDVector.h>
#include <Rendering/VDRender.h>
#include <Rendering/VDRenderSetting.h>
#include <stddef.h>
#include <VDDef.h>

/**
 *
 */
class VDDECLSPEC VDRenderPipeLine{
public:

	/**
	 *	Main rendering method.
	 *
	 *	\allocator Used for fast allocation of memory.
	 */
	static void VDAPIENTRY render(VDDoubleBufferedAllocator* allocator);

	/**
	 *	Render from camera perspective and store frame to rendertarget
	 *	assoicated with the camera object.
	 */
	static void VDAPIENTRY drawCamera(VDCamera* camera, VDDoubleBufferedAllocator* allocator);

	/**
	 *	Final render pass. Applying Post Effect In Chronlogic to the
	 *	array. Post Effect Will be blended togheter.
	 *
	 *	\camera
	 *
	 *	\path
	 */
	static void VDAPIENTRY renderPostEffect(VDCamera* camera, VDRenderSetting::RenderPipeline path);


	/**
	 *	Draw lights visiable in cameras frustm.
	 */
	static void VDAPIENTRY drawLight(VDCamera* camera, VDDoubleBufferedAllocator* allocator);
	static void VDAPIENTRY drawShadowTask(VDTaskSchedule::VDTaskPackage* package);

	/**
	 *
	 */
	static void bindShadowMaps(VDCamera* camera);

	/**
	 *
	 */
	static void occlude(VDFrustum* camera, VDDoubleBufferedAllocator* allocator);

	/**
	 *
	 */
	static void occludeTask(VDTaskSchedule::VDTaskPackage* package);
	static void particleTask(VDTaskSchedule::VDTaskPackage* package);


public:	/*	Main rendering pipeline.	*/

	/**
	 *	Forward rendering pipeline. Used for graphic adapater with low memory or low shader-model.
	 */
	static void VDAPIENTRY internalForwardRendering(VDFrustum* frustum,
	        VDCamera* camera, VDDoubleBufferedAllocator* allocator,
	        VDQueue<VDRenderer*>* renderers = NULL);

	/**
	 *	Deferred rendering used for scene with a lot of lights.
	 */
	static void VDAPIENTRY internalDefferdRendering(VDFrustum* frustum,
	        VDCamera* camera, VDDoubleBufferedAllocator* allocator,
	        VDQueue<VDRenderer*>* renderers = NULL);

	/*	*/
	static VDVector< VDQueue<VDRenderer*>> queues;
};


typedef struct vd_command_queue{

}VDCommandQueue;


#endif
