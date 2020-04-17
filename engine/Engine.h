#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <SDL.h>
#include <SDL_image.h>
#include "AssetManager.h"
#include "GameObjectManager.h"
#include "InputManager.h"

namespace ecs
{
	class Engine
	{
	public:
		static SDL_Renderer*		Renderer;
		static SDL_Rect*			Camera;
		static AssetManager*		AssetMgr;
		static GameObjectManager*	GameObjectMgr;
		static InputManager*		InputMgr;

		bool Init();
		void Quit();
		void GameLoop();
		void ProcessInput();
		void HandleGameEvents();
		void Update();
		void Render();

	private:
		SDL_Window* m_window;
		bool		m_running;
		float		m_deltaTime;

	};
}
#endif // !__ENGINE_H__

