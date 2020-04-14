#include "SoundManager.h"

namespace ecs
{
	Mix_Chunk* SoundManager::LoadFromFile(const char* filename, int volume)
	{
		Mix_Chunk* sfx = Mix_LoadWAV(filename);
		if (!sfx)
		{
			SDL_Log("Failed to load sound %s", filename);
			return nullptr;
		}
		SetVolume(sfx, volume);
		return sfx;
	}

	void SoundManager::SetVolume(Mix_Chunk* sound, int volume)
	{
		Mix_VolumeChunk(sound, volume);
	}

	void SoundManager::Free(Mix_Chunk* music)
	{
		Mix_FreeChunk(music);
	}
}