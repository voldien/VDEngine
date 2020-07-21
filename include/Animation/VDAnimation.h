/**
    VDEngine virtual dimension
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
#ifndef _VD_ANIMATION_H_
#define _VD_ANIMATION_H_ 1
#include"VDAnimationClip.h"
#include"../Core/VDBehavior.h"
#include"../VDDef.h"

/**
 *	Gameobject componenets for adding
 *	animation.
 */
class VDDECLSPEC VDAnimation: public VDBehavior {
public:
	enum AnimationState {
		eNone = 0x0, /*	*/
		eIsPlaying = 0x1, /*	*/
		eIsQueed = 0x2, /*	*/
		eIsBlend = 0x4, /*	*/
	};

	VDAnimation(void);
	VDAnimation(const VDAnimation& animation);

	/**
	 *
	 */
	virtual void instanceInitilize(void);
	virtual void onEnable(void);
	virtual void onDisable(void);
	virtual void initializeComponent(void);
	virtual void onDestroy(void);
	virtual VDBehavior* copyComponent(unsigned int& dataSize);

	/**
	 *	Check if animation is playing.
	 *
	 *	@Return true if currently playing.
	 */
	bool VDAPIFASTENTRY isPlaying(void) const;

	/**
	 *	Get animation current state.
	 *
	 *	@Return
	 */
	inline AnimationState getCurrentState(void) const {
		return (AnimationState) this->animationState;
	}

	/**
	 *	Blend current animation with new animation.
	 *
	 *	@Return
	 */
	int VDAPIENTRY blend(VDAnimationClip* animationClip, float blendWeight =
			1.0f);

	/**
	 *	Blend current animation with new animation.
	 *
	 *	@Return
	 */
	int VDAPIENTRY blend(const char* animationClip);

	/**
	 *	Start play animation clip.
	 */
	void VDAPIFASTENTRY play(int clipIndex = 0);

	/**
	 *	Start play animation clip.
	 */
	void VDAPIFASTENTRY play(const char* animationClip);

	/**
	 *	Stop animation playback.
	 */
	void VDAPIENTRY stop(void);

	/**
	 *	Add clip.
	 */
	void VDAPIFASTENTRY addClip(VDAnimationClip* animationClip);

	/**
	 *	Get clip by index.
	 *	@Return None null if valid index.
	 */
	VDAnimationClip* VDAPIFASTENTRY getClip(int index) const;

	/**
	 *	@Return Number of animation clips.
	 */
	unsigned int VDAPIENTRY getNumClips(void) const;

	/**
	 *	Remove animation clip by index if valid.
	 */
	void VDAPIENTRY removeClip(unsigned int index);

	/*
	 *	Remove animation clip by name if exists.
	 */
	void VDAPIENTRY removeClip(const char* cname);

	/**
	 *	Get current animation clip being played.
	 *
	 *	@Return Non null if currently playing.
	 */
	VDAnimationClip* VDAPIENTRY getCurrentPlayingClip(void);

	/**
	 *
	 */
	void VDAPIENTRY internalUpdate(void);

	/**
	 *	transformation will have a specified float of
	 *	reading the information.
	 */
	void VDAPIENTRY internalCurveUpdate(unsigned int index);

	/**
	 *
	 */
	void VDAPIENTRY setAnimationOnStep(float time);

private:
	/*	Attributes.	*/

	VDVector<VDAnimationClip*> clips; 	/*	Array of animation clips.	*/
	double time; 						/*	Current time of animation.	*/
	AnimationState animationState; 		/*	Animation state.	*/

	/*	TODO conclude if needed.	*/
	int currentkeyframe;

};

#endif
