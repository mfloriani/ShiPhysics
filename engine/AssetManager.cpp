#include "AssetManager.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "SoundManager.h"
#include "MusicManager.h"
#include "Constants.h"

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

	bool AssetManager::AddSound(std::string id, std::string filePath)
	{
		Mix_Chunk* sound = SoundManager::LoadFromFile(filePath.c_str(), SOUND_VOLUME);
		if (!sound)
		{
			return false;
		}
		_sounds.insert(std::make_pair(id, sound));
		return true;
	}

	bool AssetManager::AddMusic(std::string id, std::string filePath)
	{
		Mix_Music* music = MusicManager::LoadFromFile(filePath.c_str());
		if (!music)
		{
			return false;
		}
		_musics.insert(std::make_pair(id, music));
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

	Mix_Chunk* AssetManager::GetSound(std::string id) const
	{
		auto sound = _sounds.find(id);
		if (sound != _sounds.end())
		{
			return sound->second;
		}
		return nullptr;
	}

	Mix_Music* AssetManager::GetMusic(std::string id) const
	{
		auto music = _musics.find(id);
		if (music != _musics.end())
		{
			return music->second;
		}
		return nullptr;
	}

	bool AssetManager::HasTexture(std::string id) const
	{
		if (_textures.find(id) != _textures.end())
		{
			return true;
		}
		return false;
	}

	bool AssetManager::HasFont(std::string id) const
	{
		if (_fonts.find(id) != _fonts.end())
		{
			return true;
		}
		return false;
	}

	bool AssetManager::HasSound(std::string id) const
	{
		if (_sounds.find(id) != _sounds.end())
		{
			return true;
		}
		return false;
	}

	bool AssetManager::HasMusic(std::string id) const
	{
		if (_musics.find(id) != _musics.end())
		{
			return true;
		}
		return false;
	}

	void AssetManager::PlayMusic(std::string id)
	{
		if (!HasMusic(id))
		{
			return;
		}
		MusicManager::SetVolume(MUSIC_VOLUME);
		MusicManager::Play(GetMusic(id));
	}

	void AssetManager::PlaySound(std::string id)
	{

	}

	void AssetManager::Free()
	{
		for (auto const&[id, texture] : _textures)
		{
			TextureManager::Free(texture);
		}

		for (auto const&[id, font] : _fonts)
		{
			FontManager::Free(font);
		}

		for (auto const&[id, sound] : _sounds)
		{
			SoundManager::Free(sound);
		}

		for (auto const&[id, music] : _musics)
		{
			MusicManager::Free(music);
		}
	}
}