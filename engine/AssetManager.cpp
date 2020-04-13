#include "AssetManager.h"
#include "TextureManager.h"
#include "FontManager.h"

namespace ecs
{
	AssetManager::AssetManager()
	{
	}

	AssetManager::~AssetManager()
	{
	}

	bool AssetManager::AddTexture(std::string id, std::string filePath)
	{
		SDL_Texture* texture = TextureManager::LoadFromFile(filePath.c_str());
		if (!texture)
		{
			return false;
		}
		_textures.insert(std::make_pair(id, texture));
		return true;
	}

	bool AssetManager::AddFont(std::string id, std::string filePath, int size)
	{
		TTF_Font* font = FontManager::LoadFromFile(filePath.c_str(), size);
		if (!font)
		{
			return false;
		}
		_fonts.insert(std::make_pair(id, font));
		return true;
	}

	SDL_Texture* AssetManager::GetTexture(std::string id) const
	{
		auto texture = _textures.find(id);
		if (texture != _textures.end())
		{
			return texture->second;
		}
		return nullptr;
	}

	TTF_Font* AssetManager::GetFont(std::string id) const
	{
		auto font = _fonts.find(id);
		if (font != _fonts.end())
		{
			return font->second;
		}
		return nullptr;
	}

	bool AssetManager::HasFont(std::string id) const
	{
		if (_fonts.find(id) != _fonts.end())
		{
			return true;
		}
		return false;
	}

	void AssetManager::Free()
	{
		for (auto const&[id, texture] : _textures)
		{
			SDL_DestroyTexture(texture);
		}

		for (auto const&[id, font] : _fonts)
		{
			TTF_CloseFont(font);
		}
	}
}