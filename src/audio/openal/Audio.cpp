#include"VDAudio.h"
#include<AL/al.h>
#include<AL/alc.h>

ALCdevice *g_audiodevice;
ALCcontext *g_audiocontext;

int VDAudio::init(void){
	const ALCchar *defaultDevice = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
	if (defaultDevice == NULL) return 0;

	g_audiodevice = alcOpenDevice(defaultDevice);
	if (g_audiodevice == NULL) return 0;

	g_audiocontext = alcCreateContext(g_audiodevice, NULL);
	if (g_audiocontext == NULL) return 0;

	if (alcMakeContextCurrent(g_audiocontext) == AL_FALSE) return 0;

	return 1;
}

void VDAudio::release(void){
	alcDestroyContext(g_audiocontext);
	g_audiocontext = NULL;
	g_audiodevice = NULL;
}
