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

#ifndef SOLOUD_WAVSTREAM_H
#define SOLOUD_WAVSTREAM_H

#include <stdio.h>
#include "soloud.h"


struct stb_vorbis;

namespace SoLoud
{
	class WavStream;

	class WavStreamInstance : public AudioSourceInstance
	{
		WavStream *mParent;
		int mOffset;
		FILE *mFile;
		stb_vorbis *mOgg;
		int mOggFrameSize;
		int mOggFrameOffset;
		float **mOggOutputs;
	public:
		WavStreamInstance(WavStream *aParent);
		virtual void getAudio(float *aBuffer, int aSamples);
		virtual int rewind();
		virtual int hasEnded();
		virtual ~WavStreamInstance();
	};

	class WavStream : public AudioSource
	{
		void loadwav(FILE * fp);
		void loadogg(FILE * fp);
	public:
		int mOgg;
		char *mFilename;
		int mDataOffset;
		int mBits;
		int mChannels;
		int mSampleCount;

		WavStream();
		virtual ~WavStream();
		void load(const char *aFilename);
		virtual AudioSourceInstance *createInstance();
	};
};

#endif