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
#ifndef _VD_ANIMATION_CLIP_H_
#define _VD_ANIMATION_CLIP_H_ 1
#include"../VDDef.h"
#include"VDCurve.h"
#include<vector>

/**
 *
 */
typedef std::vector<VDCurve> VDCurveList;

/**
 *	Animation clip. Containts curves.
 */
class VDDECLSPEC VDAnimationClip: public VDAssetObject {
public:

	/**
	 *
	 */
	enum AnimationClipState {
		eDefault = 0x1, /*	Default.	*/
		eOnce = 0x2, /*	Play animation once.	*/
		eLoop = 0x4, /*	Loop clip.	*/
		ePingPong = 0x8 /*	play clip ping pong mode.	*/
	};

	VDAnimationClip(void);
	VDAnimationClip(float duration, float frameTicks);
	VDAnimationClip(const VDAnimationClip& animationClip);
	~VDAnimationClip(void);

private:
	/*	Attributes.	*/

	VDCurveList curves; /*	*/
	float duration; /*	Total length of the animation clip.	*/
	float frameTicks; /*	*/
	AnimationClipState animationState; /*	*/

public:
	/*	Public methods.	*/

	/**
	 *	Get curve list.
	 *	@Return
	 */
	inline const VDCurveList* getCurves(void) const {
		return &this->curves;
	}

	/**
	 *	@Return
	 */
	inline AnimationClipState getState(void) const {
		return this->animationState;
	}

	/**
	 *	@Return
	 */
	inline VDCurve& getCurve(int index) {
		return this->curves[index];
	}

	/**
	 *	@Return
	 */
	inline unsigned int getNumCurves(void) const {
		return this->curves.size();
	}

	/**
	 *	@Return curve duration time in seconds.
	 */
	inline float getDuration(void) const {
		return this->duration;
	}

	/**
	 *	@Return
	 */
	inline bool isLoop(void) const {
		return (this->getState() & eLoop) != 0;
	}

	/**
	 *	@Return
	 */
	inline bool isPingPong(void) const {
		return (this->getState() & ePingPong) != 0;
	}

	/**
	 *	Release resources.
	 */
	void VDAPIENTRY release(void);

	/**
	 *	Add curve in the curve list.
	 */
	void VDAPIENTRY addCurve(const VDCurve& curve);

	/**
	 *
	 */
	void VDAPIENTRY reIndex(void);

	/**
	 *	Initialize the Animation Clip related to its relationship
	 */
	void VDAPIENTRY findNodeDataPointer(VDTransform* transform);

};

#endif
