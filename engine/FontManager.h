#ifndef __FONT_MANAGER_H__
#define __FONT_MANAGER_H__

#include <SDL_ttf.h>

namespace ecs
{
	class FontManager
	{
	public:
		static TTF_Font* LoadFromFile(const char* filename, int size);
		static void Render(SDL_Texture* texture, SDL_Rect position);
	};
}

#endif // !__FONT_MANAGER_H__

