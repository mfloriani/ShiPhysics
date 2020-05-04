#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <SDL.h>

namespace ecs
{
	class AssetManager;
	class GameObjectManager;
	class InputSystem;
	class PhysicsSystem;

	class Engine
	{
	public:
		static SDL_Renderer*		Renderer;
		static SDL_Rect*			Camera;
		static AssetManager*		AssetMgr;
		static GameObjectManager*	GameObjectMgr;
		static InputSystem*			InputSys;
		static PhysicsSystem*		PhysicsSys;

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

