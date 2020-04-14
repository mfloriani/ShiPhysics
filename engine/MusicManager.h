#ifndef __MUSIC_MANAGER_H__
#define __MUSIC_MANAGER_H__

#include <SDL.h>
#include <SDL_mixer.h>

namespace ecs
{
	class MusicManager
	{
	public:
		static Mix_Music* LoadFromFile(const char* fileName);
		static void SetVolume(int volume);
		static void Play(Mix_Music* music);
		static void Free(Mix_Music* music);
	};
}

#endif // !__MUSIC_MANAGER_H__

