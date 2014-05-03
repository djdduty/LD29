/*
SoLoud audio engine
Copyright (c) 2013 Jari Komppa

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/
#include <stdlib.h>
#if defined(_MSC_VER)
#include "../../SDL2/include/SDL.h"
#else
#include "SDL/SDL.h"
#endif
#include <math.h>

#include "soloud.h"

namespace SoLoud
{
	void soloud_sdl_audiomixer(void *userdata, Uint8 *stream, int len)
	{
		int samples = len / 4;
		short *buf = (short*)stream;
		SoLoud::Soloud *soloud = (SoLoud::Soloud *)userdata;
		float *mixdata = (float*)(soloud->mBackendData);
		soloud->mix(mixdata, samples);

		int i;
		for (i = 0; i < samples*2; i++)
		{
			buf[i] = (short)(mixdata[i] * 0x7fff);
		}
	}

	void soloud_sdl_lockmutex(void *aMutexPtr)
	{
		SDL_mutexP((SDL_mutex*)aMutexPtr);
	}

	void soloud_sdl_unlockmutex(void *aMutexPtr)
	{
		SDL_mutexV((SDL_mutex*)aMutexPtr);
	}

	static void soloud_sdl_deinit(SoLoud::Soloud *aSoloud)
	{
		SDL_CloseAudio();
		delete[] (float*)aSoloud->mBackendData;
		SDL_DestroyMutex((SDL_mutex*)aSoloud->mMutex);
	}

	int sdl_init(SoLoud::Soloud *aSoloud, int aFlags, int aSamplerate, int aBuffer)
	{
		aSoloud->mMutex = SDL_CreateMutex();
		SDL_AudioSpec as;
		as.freq = aSamplerate;
		as.format = AUDIO_S16;
		as.channels = 2;
		as.samples = aBuffer;
		as.callback = soloud_sdl_audiomixer;
		as.userdata = (void*)aSoloud;

		SDL_AudioSpec as2;
		if (SDL_OpenAudio(&as, &as2) < 0)
		{
			return 1;
		}
		aSoloud->mBackendData = new float[as2.samples*4];

		aSoloud->init(as2.freq, as2.samples * 2, aFlags);

		aSoloud->mLockMutexFunc = soloud_sdl_lockmutex;
		aSoloud->mUnlockMutexFunc = soloud_sdl_unlockmutex;
		aSoloud->mBackendCleanupFunc = soloud_sdl_deinit;

		SDL_PauseAudio(0);
		return 0;
	}
	
};
