#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <SDL_image.h>

namespace ecs
{
	class TextureManager
	{
	public:
		static SDL_Texture* LoadFromFile(const char* fileName);
		static void Render(SDL_Texture* texture);
		static void Render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect);
		static void Render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, float angle);
		static void Render(SDL_Texture* texture, SDL_Rect* dstRect, float angle);
		static void Render(SDL_Texture* texture, SDL_Rect* srcRect, SDL_Rect* dstRect, float angle, SDL_RendererFlip flip);
	};
}

#endif
