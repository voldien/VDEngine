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
#ifndef _VD_AUDIO_CLIP_H_
#define _VD_AUDIO_CLIP_H_ 1
#include"../Asset/VDAssetObject.h"

#if defined(VD_INTERNAL) && defined(USE_FMOD)
	#include<fmod/fmod.hpp>
	#define FMODNAMESPACE FMOD
#endif

/**
 *
 */
class VDDECLSPEC VDAudioClip : public VDAssetObject{
public:

	/**
	 *
	 */
	enum Format{
		eStream = 		0x1,	/*	Stream from file.	*/
		eCompressed = 		0x2,	/*	Compressed on the f*/
		eIs3D = 		0x4,	/*	*/
		eIs2D = 		0x8,	/*	*/
		eStreamSource = 	0x10,	/*	*/
	};

	VDAudioClip(void);
	VDAudioClip(const VDAudioClip& audio);
	VDAudioClip(const char* path, Format bitFlag = (Format)(eIs2D | eCompressed) );
	~VDAudioClip(void);


	/**
	 *	Method responsible for releasing
	 *	resources associate with this object.
	 */
	virtual void VDAPIENTRY release(void);

	/**
	 *	Set type of audio clip.
	 *	\type compress, raw, stream. etc.
	 */
	int VDAPIENTRY setClipType(unsigned int type);

	/**
	 *	Check if audio is a 3D audio clip.
	 *	@Return true if 3D, false otherwise.
	 */
	bool VDAPIFASTENTRY is3D(void);

	/**
	 *	Check if audio is 2D.
	 *	@Return true if 2D, otherwise false.
	 */
	bool VDAPIFASTENTRY is2D(void);

	/**
	 *
	 *	@Return
	 */
	int VDAPIENTRY load(const char* path, unsigned int dataBitFlag = eIs3D | eCompressed);

	/**
	 *
	 *	@Return
	 */
	void* getSoundTrack(void)const{return soundTrack;}


	/**
	 *
	 */
	void VDAPIENTRY write(void* buffer, int rSize);

	/**
	 *
	 *	@Return
	 */
	void* VDAPIENTRY read(int rSize);

	/**
	 *
	 */
	static void VDAPIENTRY assigneClip(VDAudioClip* shader);

private:	/*	*/

	union{
#if defined(VD_INTERNAL) && defined(USE_FMOD)
	FMODNAMESPACE::Sound* soundTrack;
#else
	void* soundTrack;
#endif
	};
};

#endif
