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
#ifndef _VD_AUDIO_SETTINGS_H_
#define _VD_AUDIO_SETTINGS_H_ 1
#include"VDAudioClip.h"
#include"VDAudioSource.h"

/**
 *
 */
class VDDECLSPEC VDAudioSetting{
public:

	/**
	 *	Speaker mode
	 */
	enum SpeakerMode{
	    eRaw,              	/* There is no specific speakermode.  Sound channels are mapped in order of input to output.  Use System::setSoftwareFormat to specify speaker count. See remarks for more information. */
		eMono,	 			/* The speakers are monaural. */
		eStereo,			/* The speakers are stereo (DEFAULT). */
	    eQUAD,             	/* 4 speaker setup.  This includes front left, front right, rear left, rear right.  */
	    eSURROUND,         	/* 5 speaker setup.  This includes front left, front right, center, rear left, rear right. */
	    e5POINT1,          	/* 5.1 speaker setup.  This includes front left, front right, center, rear left, rear right and a subwoofer. */
	    e7POINT1,          	/* 7.1 speaker setup.  This includes front left, front right, center, rear left, rear right, side left, side right and a subwoofer. */
		eUnknown,
	};

	/**
	 *
	 */
	enum Format{
	    eNone,				/* Unitialized / unknown. */
	    ePCM8,				/* 8bit integer PCM data. */
	    ePCM16,				/* 16bit integer PCM data. */
	    ePCM24,				/* 24bit integer PCM data. */
	    ePCM32,				/* 32bit integer PCM data. */
	    ePCMFLOAT,			/* 32bit floating point PCM data. */
	    eGCADPCM,			/* Compressed Nintendo 3DS/Wii DSP data. */
	    eIMAADPCM,			/* Compressed IMA ADPCM data. */
	    eVAG,				/* Compressed PlayStation Portable ADPCM data. */
	    eHEVAG,				/* Compressed PSVita ADPCM data. */
	    eXMA,				/* Compressed Xbox360 XMA data. */
	    eMPEG,				/* Compressed MPEG layer 2 or 3 data. */
	    eCELT,				/* Compressed CELT data. */
	    eAT9,				/* Compressed PSVita ATRAC9 data. */
	    eXWMA,				/* Compressed Xbox360 xWMA data. */
	    eVORBIS,			/* Compressed Vorbis data. */

	    eMAX,				/* Maximum number of sound formats supported. */
	    eFORCEINT = 65536	/* Makes sure this enum is signed 32bit. */
	};

	/**/
	static bool VDAPIFASTENTRY isEnable(void);
	static bool VDAPIFASTENTRY isDisable(void);


	/**
	 *	Set main volume parameter of the application.
	 */
	static void VDAPIENTRY setMasterVolume(float volume);

	/**
	 *	Get main volume of the application.
	 *
	 *	@Return
	 */
	static float VDAPIENTRY getMasterVolume(void);

	/*
	 *	Set speaker mode of the application.
	 */
	static void VDAPIENTRY setSpeakMode(SpeakerMode speakermode);

	/**
	 *	Get speaker mode of the application.
	 *
	 *	@Return
	 */
	static SpeakerMode VDAPIENTRY getSpeakerMode(void);

	/**
	 *	Get output sample rate.
	 *
	 *	@Return
	 */
	static int VDAPIENTRY getSampleRate(void);

	/**
	 *	Set output sample rate.
	 */
	static void VDAPIENTRY setSampleRate(int sampleRate);

	/**
	 *	Get audio data format.
	 *
	 *	@Return
	 */
	static Format VDAPIENTRY getFormat(void);

	/*'
	 *	Set audio data format.
	 */
	static void VDAPIENTRY setFormat(Format format);

	/**
	 *	Get volume speed.
	 *
	 *	@Return
	 */
	static int VDAPIENTRY getVolumeSpeed(void);

	/**
	 *	set volume speed.
	 */
	static void VDAPIENTRY setVolumeSpeed(int volumeSpeed);

};

#endif
