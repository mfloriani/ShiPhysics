#include "Engine.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Constants.h"
#include "AssetManager.h"
#include "GameObjectManager.h"
#include "InputSystem.h"
#include "PhysicsSystem.h"
#include "GameObject.h"


namespace ecs
{
	SDL_Renderer*		Engine::Renderer = nullptr;
	SDL_Rect*			Engine::Camera = nullptr;
	AssetManager*		Engine::AssetMgr = nullptr;
	GameObjectManager*	Engine::GameObjectMgr = nullptr;
	InputSystem*		Engine::InputSys = nullptr;
	PhysicsSystem*		Engine::PhysicsSys = nullptr;
	

	bool Engine::Init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL! SDL_Error: %s", SDL_GetError());
			return false;
		}
		m_window = SDL_CreateWindow("ShiPhysics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
		if (!m_window)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create SDL_WINDOW: %s", SDL_GetError());
			return false;
		}

		Renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!Renderer)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create SDL_RENDERER: %s", SDL_GetError());
			return false;
		}
		SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL_IMAGE: %s", IMG_GetError());
			return false;
		}
		if (TTF_Init() == -1)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL_TTF: %s", TTF_GetError());
			return false;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize SDL_MIXER: %s\n", Mix_GetError());
			return false;
		}

		Camera = new SDL_Rect{ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
		AssetMgr = new AssetManager;
		GameObjectMgr = new GameObjectManager;
		InputSys = new InputSystem;
		PhysicsSys = new PhysicsSystem(GameObjectMgr);

		m_running = true;

		return true;
	}

	void Engine::Quit()
	{
		delete PhysicsSys;
		PhysicsSys = nullptr;

		delete InputSys;
		InputSys = nullptr;

		delete Camera;
		Camera = nullptr;

		delete AssetMgr;
		AssetMgr = nullptr;

		delete GameObjectMgr;
		GameObjectMgr = nullptr;

		SDL_DestroyRenderer(Renderer);
		Renderer = nullptr;

		SDL_DestroyWindow(m_window);
		m_window = nullptr;

		Mix_Quit();
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	void Engine::GameLoop()
	{
		m_ticksLastFrame = SDL_GetTicks();
		while (m_running)
		{
			HandleFPS();

			ProcessInput();

			HandleGameEvents();

			Update();

			Render();
		}
	}

	inline void Engine::HandleFPS()
	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticksLastFrame + FRAME_LENGTH));
		m_deltaTime = (SDL_GetTicks() - m_ticksLastFrame) / 1000.f;
		m_ticksLastFrame = SDL_GetTicks();
		if (m_deltaTime > 0.1f) m_deltaTime = 0.1f;
	}

	inline void Engine::ProcessInput()
	{
		InputSys->Update();
	}

	inline void Engine::HandleGameEvents()
	{
		for (auto event : InputSys->GetEvents())
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			{
				m_running = false;
			}
		}
	}

	inline void Engine::Update()
	{
		for (auto go : GameObjectMgr->m_gameObjects)
		{
			go->Update(m_deltaTime);
		}

		PhysicsSys->Update(m_deltaTime);

		GameObjectMgr->AddNewGameObjectsToPipeline();
	}

	inline void Engine::Render()
	{
		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(Renderer);

		for (auto go : GameObjectMgr->m_gameObjects)
		{
			go->Render();
		}

		SDL_RenderPresent(Renderer);
	}
}