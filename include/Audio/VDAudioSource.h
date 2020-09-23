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
#ifndef _VD_AUDIOSOURCE_H_
#define _VD_AUDIOSOURCE_H_ 1
#include<fragcore/audio/AudioSource.h>
#include"../Core/VDBehavior.h"
#include"../VDDef.h"

/**
 *
 */
class VDDECLSPEC VDAudioSource : public VDBehavior{
public:
	VDAudioSource(void);
	VDAudioSource(const VDAudioSource& source);

	virtual void instanceInitilize(void);
	virtual void onEnable(void);
	virtual void onDisable(void);
	virtual void onDestroy(void);
	virtual void initializeComponent(void);
	virtual VDBehavior* copyComponent(unsigned int& dataSize);

	/**
	 *	Set current audio clip.
	 */
	void setClip(VDAudioClip* clip);

	/**
	 *	Get current audio clip.
	 *	@Return non null if clip exists.
	 */
	VDAudioClip* getClip(void)const;

	/**
	 *	Start playback.
	 */
	void VDAPIFASTENTRY play(void);

	/**
	 *	Pause current playback.
	 */
	void VDAPIFASTENTRY pause(void);

	/**
	 *	Stop current playback.
	 */
	void VDAPIFASTENTRY stop(void);

	/**
	 *	Set mute state.
	 */
	void VDAPIENTRY mute(bool mute);

	/**
	 *	Set loop state.
	 */
	void VDAPIENTRY loop(bool loop);

	/**
	 *	Check if playback is currently.
	 */
	bool VDAPIFASTENTRY isPlaying(void)const;

public:

	/**
	 *
	 *	@Return
	 */
	float VDAPIFASTENTRY getFrequency(void)const;

	/**
	 *
	 */
	void VDAPIFASTENTRY setFrequency(float frequency);

	/**
	 *	Set volume of audio source.
	 */
	void VDAPIENTRY setVolume(float volume);

	/**
	 *
	 *	@Return
	 */
	float VDAPIENTRY getVolume(void)const;

	/**
	 *	Set priority of the audio source.
	 */
	void VDAPIENTRY setPriority(int Priority);

	/**
	 *	Get current priority of the
	 *	audio source.
	 */
	int VDAPIENTRY getPriority(void)const;
	
	/**
	 *	Set max hearing distance.
	 */
	void VDAPIENTRY setMaxDistance(float Maxdistance);

	/**
	 *	Get max hearing distance.
	 */
	float VDAPIENTRY getMaxDistance(void)const;

	/**
	 *	Set min hearing distance.
	 */
	void VDAPIENTRY setMinDistance(float Mindistance);

	/**
	 *	Get min hearing distance.
	 */
	float VDAPIENTRY getMinDistance(void)const;

public:

	/**
	 *	Update current audio source.
	 */
	void VDAPIENTRY update(void);

	/**
	 *	update all audioSources.
	 */
	static void VDAPIENTRY AudioMechanicUpdate(VDDoubleBufferedAllocator* allocator = NULL);

private:	/*	Attributes.	*/
 fragcore::AudioSource* source;
 VDAudioClip* clip; /*	Audio clip assoicated with the audio clip.	*/

 union {
#if defined(VD_INTERNAL) && defined(USE_FMOD)
	FMODNAMESPACE::Channel* channel;
#else
	void* channel;
#endif
	};

};


#endif
