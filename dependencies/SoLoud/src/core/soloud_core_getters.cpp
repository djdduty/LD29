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

#include "soloud.h"

// Getters - return information about SoLoud state

namespace SoLoud
{
	float Soloud::getPostClipScaler() const
	{
		return mPostClipScaler;
	}

	float Soloud::getGlobalVolume() const
	{
		return mGlobalVolume;
	}

	int Soloud::getHandleFromVoice(int aVoice) const
	{
		if (mVoice[aVoice] == 0)
			return 0;
		return (aVoice + 1) | (mVoice[aVoice]->mPlayIndex << 12);
	}

	int Soloud::getVoiceFromHandle(int aVoiceHandle) const
	{
		if (aVoiceHandle < 0) 
		{
			return -1;
		}
		int ch = (aVoiceHandle & 0xfff) - 1;
		unsigned int idx = aVoiceHandle >> 12;
		if (mVoice[ch] &&
			(mVoice[ch]->mPlayIndex & 0xfffff) == idx)
		{
			return ch;
		}
		return -1;		
	}

	int Soloud::getActiveVoiceCount() const
	{
		if (mLockMutexFunc) mLockMutexFunc(mMutex);
		int i;
		int c = 0;
		for (i = 0; i < VOICE_COUNT; i++)
		{
			if (mVoice[i]) 
			{
				c++;
			}
		}
		if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
		return c;
	}

	int Soloud::isValidVoiceHandle(int aVoiceHandle) const
	{
		if (mLockMutexFunc) mLockMutexFunc(mMutex);
		if (getVoiceFromHandle(aVoiceHandle) != -1) 
		{
			if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
			return 1;
		}
		if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
		return 0;
	}


	float Soloud::getVolume(int aVoiceHandle) const
	{
		if (mLockMutexFunc) mLockMutexFunc(mMutex);
		int ch = getVoiceFromHandle(aVoiceHandle);
		if (ch == -1) 
		{
			if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
			return 0;
		}
		float v = mVoice[ch]->mVolume;
		if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
		return v;
	}

	float Soloud::getPan(int aVoiceHandle) const
	{
		if (mLockMutexFunc) mLockMutexFunc(mMutex);
		int ch = getVoiceFromHandle(aVoiceHandle);
		if (ch == -1) 
		{
			if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
			return 0;
		}
		float v = mVoice[ch]->mPan;
		if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
		return v;
	}

	float Soloud::getStreamTime(int aVoiceHandle) const
	{
		if (mLockMutexFunc) mLockMutexFunc(mMutex);
		int ch = getVoiceFromHandle(aVoiceHandle);
		if (ch == -1) 
		{
			if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
			return 0;
		}
		float v = mVoice[ch]->mStreamTime;
		if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
		return v;
	}

	float Soloud::getRelativePlaySpeed(int aVoiceHandle) const
	{
		if (mLockMutexFunc) mLockMutexFunc(mMutex);
		int ch = getVoiceFromHandle(aVoiceHandle);
		if (ch == -1) 
		{
			if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
			return 1;
		}
		float v = mVoice[ch]->mRelativePlaySpeed;
		if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
		return v;
	}

	float Soloud::getSamplerate(int aVoiceHandle) const
	{
		if (mLockMutexFunc) mLockMutexFunc(mMutex);
		int ch = getVoiceFromHandle(aVoiceHandle);
		if (ch == -1) 
		{
			if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
			return 0;
		}
		float v = mVoice[ch]->mBaseSamplerate;
		if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
		return v;
	}

	int Soloud::getPause(int aVoiceHandle) const
	{
		if (mLockMutexFunc) mLockMutexFunc(mMutex);
		int ch = getVoiceFromHandle(aVoiceHandle);
		if (ch == -1) 
		{
			if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
			return 0;
		}
		int v = !!(mVoice[ch]->mFlags & AudioSourceInstance::PAUSED);
		if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
		return v;
	}

	int Soloud::getProtectVoice(int aVoiceHandle) const
	{
		if (mLockMutexFunc) mLockMutexFunc(mMutex);
		int ch = getVoiceFromHandle(aVoiceHandle);
		if (ch == -1) 
		{
			if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
			return 0;
		}
		int v = !!(mVoice[ch]->mFlags & AudioSourceInstance::PROTECTED);
		if (mUnlockMutexFunc) mUnlockMutexFunc(mMutex);
		return v;
	}

	int Soloud::findFreeVoice()
	{
		int i;
		unsigned int lowest_play_index_value = 0xffffffff;
		int lowest_play_index = -1;
		for (i = 0; i < VOICE_COUNT; i++)
		{
			if (mVoice[i] == NULL)
			{
				return i;
			}
			if (((mVoice[i]->mFlags & AudioSourceInstance::PROTECTED) == 0) && 
				mVoice[i]->mPlayIndex < lowest_play_index_value)
			{
				lowest_play_index_value = mVoice[i]->mPlayIndex;
				lowest_play_index = i;
			}
		}
		stopVoice(lowest_play_index);
		return lowest_play_index;
	}

}
