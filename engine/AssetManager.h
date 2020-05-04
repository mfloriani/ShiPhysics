#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


namespace ecs
{
	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager();
		
		bool AddTexture(std::string id, std::string filePath);
		bool AddFont(std::string id, std::string filePath, int size);
		bool AddSound(std::string id, std::string filePath);
		bool AddMusic(std::string id, std::string filePath);
		
		SDL_Texture* GetTexture(std::string id) const;
		TTF_Font* GetFont(std::string id) const;
		Mix_Chunk* GetSound(std::string id) const;
		Mix_Music* GetMusic(std::string id) const;
		
		bool HasTexture(std::string id) const;
		bool HasFont(std::string id) const;
		bool HasMusic(std::string id) const;
		bool HasSound(std::string id) const;

		void PlayMusic(std::string id);
		void PlaySound(std::string id);

		void Free();

	private:
		std::map<std::string, SDL_Texture*> _textures;
		std::map<std::string, TTF_Font*>	_fonts;
		std::map<std::string, Mix_Chunk*>	_sounds;
		std::map<std::string, Mix_Music*>	_musics;
	};
}

#endif // !__ASSET_MANAGER_H__
