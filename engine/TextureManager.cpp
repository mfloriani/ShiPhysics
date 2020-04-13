#include "TextureManager.h"
#include "Engine.h"

namespace ecs
{
	SDL_Texture* TextureManager::LoadFromFile(const char* fileName)
	{
		SDL_Surface* surface = IMG_Load(fileName);
		if (!surface)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture %s: %s", fileName, SDL_GetError());
			return nullptr;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::Renderer, surface);
		SDL_FreeSurface(surface);
		return texture;
	}

	void TextureManager::Render(SDL_Texture* texture)
	{
		SDL_RenderCopyEx(Engine::Renderer, texture, NULL, NULL, 0.0, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
	}

	void TextureManager::Render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect)
	{
		SDL_RenderCopyEx(Engine::Renderer, texture, srcRect, dstRect, 0.0, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
	}
	
	void TextureManager::Render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, float angle)
	{
		SDL_RenderCopyEx(Engine::Renderer, texture, srcRect, dstRect, angle, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
	}

	void TextureManager::Render(SDL_Texture* texture, SDL_Rect* dstRect, float angle)
	{
		SDL_RenderCopyEx(Engine::Renderer, texture, NULL, dstRect, angle, NULL, SDL_RendererFlip::SDL_FLIP_NONE);
	}

	void TextureManager::Render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, float angle, SDL_RendererFlip flip)
	{
		SDL_RenderCopyEx(Engine::Renderer, texture, srcRect, dstRect, angle, NULL, flip);
	}
}