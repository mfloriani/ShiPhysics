#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include <vector>
#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

namespace ecs
{
	struct Animation;

	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager();
		
		bool AddTexture(std::string id, std::string filePath);
		bool AddFont(std::string id, std::string filePath, int size);
		bool AddSound(std::string id, std::string filePath);
		bool AddMusic(std::string id, std::string filePath);
		bool AddAnimation(std::string id, std::vector<SDL_Rect> clips, uint32_t frameRate, bool loop);
		
		SDL_Texture* GetTexture(std::string id) const;
		TTF_Font* GetFont(std::string id) const;
		Mix_Chunk* GetSound(std::string id) const;
		Mix_Music* GetMusic(std::string id) const;
		Animation* GetAnimation(std::string id) const;
		
		bool HasTexture(std::string id) const;
		bool HasFont(std::string id) const;
		bool HasMusic(std::string id) const;
		bool HasSound(std::string id) const;
		bool HasAnimation(std::string id) const;

		void PlayMusic(std::string id);
		void PlaySound(std::string id);

		void Free();

	private:
		std::map<std::string, SDL_Texture*> _textures;
		std::map<std::string, TTF_Font*>	_fonts;
		std::map<std::string, Mix_Chunk*>	_sounds;
		std::map<std::string, Mix_Music*>	_musics;
		std::map<std::string, Animation*>	_animations;
	};
}

#endif // !__ASSET_MANAGER_H__
