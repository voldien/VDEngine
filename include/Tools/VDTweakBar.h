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
#ifndef _VD_TWEAK_BAR_H_
#define _VD_TWEAK_BAR_H_ 1
#include"VDToolBase.h"

/**
 *
 */
class VDDECLSPEC VDTweakBar : public VDToolBase{
public:

	/**
	 *
	 */
	typedef struct tweak_callback_attribute_t{
		unsigned int type;		/*	*/
		union{
			void* get;			/*	*/
			VDGetClassMethod mget;		/*	*/
		};
		union{
			void* set;					/*	*/
			VDSetClassMethod mset;		/*	*/
		};
		union{
			VDObject* object;
			VDGetCallBack getObject;
		};
	}VDTweakCallbackAttribute;

	VDTweakBar(void);
	~VDTweakBar(void);

	/**
	 *
	 */
	void VDAPIENTRY init(void);

	/**
	 *
	 */
	virtual void release(void);

	/**
	 *
	 */
	void VDAPIENTRY set(const VDTweakCallbackAttribute* attri);

	/**
	 *
	 */
	VDPoolAllactor<VDTweakCallbackAttribute>& VDAPIENTRY getCallBackPool(void)const;

	/**
	 *
	 */
	virtual void draw(void);

	/**
	 *
	 */
	virtual void VDAPIENTRY update(void);

	/**
	 *
	 */
	virtual void VDAPIENTRY onResize(int width, int height);

	/**
	 *
	 */
	virtual void VDAPIENTRY onMouse(int x, int y, int button);

	/**
	 *
	 */
	virtual void VDAPIENTRY onMouseWheel(int direction);

	/**/
	virtual void VDAPIENTRY onMousePressed(VDInput::Button pressed);

	/**
	 *
	 */
	virtual void VDAPIENTRY onMouseReleased(VDInput::Button released);

	/**
	 *
	 */
	virtual void VDAPIENTRY onKeyPressed(unsigned int  event);

private:	/*	attributes.	*/

	/**
	 *
	 */
	VDPoolAllactor<VDTweakCallbackAttribute> antcallback;
};

#endif
