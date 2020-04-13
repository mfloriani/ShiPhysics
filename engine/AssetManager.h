#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include <map>
#include <SDL.h>
#include <SDL_ttf.h>

namespace ecs
{
	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager();
		
		bool AddTexture(std::string id, std::string filePath);
		bool AddFont(std::string id, std::string filePath, int size);
		
		SDL_Texture* GetTexture(std::string id) const;
		TTF_Font* GetFont(std::string id) const;
		
		bool AssetManager::HasFont(std::string id) const;

		void Free();

	private:
		std::map<std::string, SDL_Texture*> _textures;
		std::map<std::string, TTF_Font*> _fonts;
	};
}

#endif // !__ASSET_MANAGER_H__
