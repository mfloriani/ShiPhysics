#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <SDL.h>
#include <SDL_image.h>
#include "AssetManager.h"

namespace ecs
{
	class Engine
	{
	public:
		static SDL_Renderer* Renderer;
		static SDL_Rect* Camera;
		static AssetManager* AssetMgr;
		bool Init();
		void Quit();

	private:
		SDL_Window* m_window;

	};
}
#endif // !__ENGINE_H__

