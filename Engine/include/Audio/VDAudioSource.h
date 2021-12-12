/*
 *	VDEngine virtual dimension game engine.
 *	Copyright (C) 2014  Valdemar Lindberg
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _VD_AUDIOSOURCE_H_
#define _VD_AUDIOSOURCE_H_ 1
#include "../Core/VDBehavior.h"
#include "../VDDef.h"
#include <AudioSource.h>

/**
 *
 */
class VDDECLSPEC VDAudioSource : public VDBehavior {
  public:
	VDAudioSource();
	VDAudioSource(const VDAudioSource &source);

	virtual void instanceInitilize();
	virtual void onEnable();
	virtual void onDisable();
	virtual void onDestroy();
	virtual void initializeComponent();
	virtual VDBehavior *copyComponent(unsigned int &dataSize);

	/**
	 *	Set current audio clip.
	 */
	void setClip(VDAudioClip *clip);

	/**
	 *	Get current audio clip.
	 *	@Return non null if clip exists.
	 */
	VDAudioClip *getClip() const;

	/**
	 *	Start playback.
	 */
	void VDAPIFASTENTRY play();

	/**
	 *	Pause current playback.
	 */
	void VDAPIFASTENTRY pause();

	/**
	 *	Stop current playback.
	 */
	void VDAPIFASTENTRY stop();

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
	bool VDAPIFASTENTRY isPlaying() const;

  public:
	/**
	 *
	 *	@Return
	 */
	float VDAPIFASTENTRY getFrequency() const;

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
	float VDAPIENTRY getVolume() const;

	/**
	 *	Set priority of the audio source.
	 */
	void VDAPIENTRY setPriority(int Priority);

	/**
	 *	Get current priority of the
	 *	audio source.
	 */
	int VDAPIENTRY getPriority() const;

	/**
	 *	Set max hearing distance.
	 */
	void VDAPIENTRY setMaxDistance(float Maxdistance);

	/**
	 *	Get max hearing distance.
	 */
	float VDAPIENTRY getMaxDistance() const;

	/**
	 *	Set min hearing distance.
	 */
	void VDAPIENTRY setMinDistance(float Mindistance);

	/**
	 *	Get min hearing distance.
	 */
	float VDAPIENTRY getMinDistance() const;

  public:
	/**
	 *	Update current audio source.
	 */
	void VDAPIENTRY update();

	/**
	 *	update all audioSources.
	 */
	static void VDAPIENTRY AudioMechanicUpdate(VDDoubleBufferedAllocator *allocator = nullptr);

  private: /*	Attributes.	*/
	fragcore::AudioSource *source;
	VDAudioClip *clip; /*	Audio clip assoicated with the audio clip.	*/

	union {
#if defined(VD_INTERNAL) && defined(USE_FMOD)
		FMODNAMESPACE::Channel *channel;
#else
		void *channel;
#endif
	};
};

#endif
