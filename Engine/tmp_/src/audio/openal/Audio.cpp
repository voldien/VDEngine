#include"VDAudio.h"
#include<AL/al.h>
#include<AL/alc.h>

ALCdevice *g_audiodevice;
ALCcontext *g_audiocontext;

int VDAudio::init(){
	const ALCchar *defaultDevice = alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
	if (defaultDevice == nullptr) return 0;

	g_audiodevice = alcOpenDevice(defaultDevice);
	if (g_audiodevice == nullptr) return 0;

	g_audiocontext = alcCreateContext(g_audiodevice, nullptr);
	if (g_audiocontext == nullptr) return 0;

	if (alcMakeContextCurrent(g_audiocontext) == AL_FALSE) return 0;

	return 1;
}

void VDAudio::release(){
	alcDestroyContext(g_audiocontext);
	g_audiocontext = nullptr;
	g_audiodevice = nullptr;
}
