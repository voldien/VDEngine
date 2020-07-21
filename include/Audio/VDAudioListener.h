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
#ifndef _VD_AUDIOLISTENER_H_
#define _VD_AUDIOLISTENER_H_ 1
#include"../Core/VDBehavior.h"
#include"../VDDef.h"


/**
 *	Used for as a listening source.
 *	Only one can exists enabled at a
 *	time.
 */
class VDDECLSPEC VDAudioListener : public VDBehavior{
public:
	VDAudioListener(void);
	VDAudioListener(const VDAudioListener& listener);

	virtual void VDAPIENTRY instanceInitilize(void);
	virtual void VDAPIENTRY onEnable(void);
	virtual void VDAPIENTRY onDisable(void);
	virtual void VDAPIENTRY onDestroy(void);
	virtual void VDAPIENTRY initializeComponent(void);
	virtual VDBehavior* VDAPIENTRY copyComponent(unsigned int& dataSize);


public:	/*	Static methods.	*/

	/**
	 *	Update current audio listener.
	 *
	 *	\allocator.
	 */
	static void VDAPIENTRY updateAudioListener(VDDoubleBufferedAllocator* allocator);

	/**
	 *	Get current audio listener.
	 *	@Return null if no audio listener exists.
	 */
	static VDAudioListener* VDAPIFASTENTRY getAudioListener(void);

	
};

#endif
