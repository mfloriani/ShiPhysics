#include "FontManager.h"
#include "Engine.h"

namespace ecs
{
	TTF_Font* FontManager::LoadFromFile(const char* filename, int size)
	{
		return TTF_OpenFont(filename, size);
	}

	void FontManager::Render(SDL_Texture* texture, SDL_Rect position)
	{
		SDL_RenderCopy(Engine::Renderer, texture, NULL, &position);
	}

	void FontManager::Free(TTF_Font* font)
	{
		TTF_CloseFont(font);
	}
}