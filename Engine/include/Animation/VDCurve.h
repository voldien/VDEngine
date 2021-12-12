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
#ifndef _VD_CURVE_H_
#define _VD_CURVE_H_ 1
#include"../Asset/VDAssetObject.h"
#include"../VDDef.h"
#include"../VDSimpleType.h"

/**
 *	Contains
 */
class VDDECLSPEC VDCurve: public VDAssetObject {
	friend VDAnimation;
	friend VDAnimationClip;
public:

	/**
	 *
	 */
	enum CurveFlag {
		eTransformPosX,
		eTransformPosY,
		eTransformPosZ,
		eTransformRotX,
		eTransformRotY,
		eTransformRotZ,
		eTransformQuadX,
		eTransformQuadY,
		eTransformQuadZ,
		eTransformQuadW,
		eTransformScaX,
		eTransformScaY,
		eTransformScaZ
	};

	VDCurve();
	VDCurve(const VDCurve& curve);
	VDCurve(int keyCount);

	/**
	 *	release the data and free the allocated curve data.
	 */
	virtual void VDAPIENTRY release();

	/**
	 *
	 */
	void VDAPIENTRY addKey(const VDKeyFrame& keyFrame, int index = -1);

	/**
	 *	@Return
	 */
	VDKeyFrame& getKey(int index);

	/**
	 *
	 */
	int getKeyCount() const;

	/**
	 *
	 */
	void VDAPIENTRY removeKey(unsigned int index);

	/**
	 *	Get Curve Value Based on Constent Linear Curve.
	 *
	 *	@Return
	 */
	float VDAPIENTRY linearInterpolation(unsigned int index, float time);

	/**
	 *	Get Curve Value based on tangent Out & In Value.
	 *
	 *	@Return
	 */
	float VDAPIENTRY tangentInterpolation(unsigned int index, float time);

	inline unsigned int getLength() const {
		return this->length;
	}

	inline unsigned int getCurveFlag() const {
		return this->cFlag;
	}

	inline void setCurveFlag(unsigned int flag) {
		this->cFlag = flag;
	}

	inline void* getPointer() const {
		return this->pointer;
	}

	inline void setPointer(void* pointer) {
		this->pointer = pointer;
	}

	void setMethodSetCallBack(VDSetClassMethod method);

	VDSetClassMethod getMethodSetCallBack() const;

	template<class T>
	void setCurveValue(T value) {
		(((VDBehavior*) this->pointer)->*getMethodSetCallBack())(
				*(void**) &value);
	}

protected:
	/*	Attributes.	*/

	VDKeyFrame* keysFrames; /**/
	unsigned int length; /**/
	void* pointer; /**/
	unsigned short cFlag; /**/
	VDSetClassMethod set; /**/

	inline VDTransform* transform() const {
		return VDCASTP(VDTransform*, this->pointer);
	}

	/**/
	template<class T>
	inline T* getPointerType() const {
		return VDCASTP(T*, this->pointer);
	}
};

#endif
