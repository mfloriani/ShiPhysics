#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include <SDL.h>
#include <SDL_mixer.h>

namespace ecs
{
	class SoundManager
	{
	public:
		static Mix_Chunk* LoadFromFile(const char* fileName, int volume);
		static void SetVolume(Mix_Chunk* sound, int volume);
		static void Free(Mix_Chunk* sound);
		static void Play(Mix_Chunk* sound);
	};
}

#endif // !__SOUND_MANAGER_H__

