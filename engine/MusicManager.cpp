#include "MusicManager.h"

namespace ecs
{
	Mix_Music* MusicManager::LoadFromFile(const char* filename)
	{
		Mix_Music* music = Mix_LoadMUS(filename);
		if (!music)
		{
			SDL_Log("Failed to load music %s", filename);
			return nullptr;
		}
		return music;
	}

	void MusicManager::SetVolume(int volume)
	{
		Mix_VolumeMusic(volume);
	}

	void MusicManager::Play(Mix_Music* music)
	{
		Mix_PlayMusic(music, -1);
	}

	void MusicManager::Free(Mix_Music* music)
	{
		Mix_FreeMusic(music);
	}
}