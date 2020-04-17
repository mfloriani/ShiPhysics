#include "Engine.h"
#include "Constants.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>

namespace ecs
{
	SDL_Renderer*		Engine::Renderer = nullptr;
	SDL_Rect*			Engine::Camera = nullptr;
	AssetManager*		Engine::AssetMgr = nullptr;
	GameObjectManager*	Engine::GameObjectMgr = nullptr;
	InputManager*		Engine::InputMgr = nullptr;

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

		Renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
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
		InputMgr = new InputManager;

		m_running = true;

		return true;
	}

	void Engine::Quit()
	{
		delete InputMgr;
		InputMgr = NULL;

		delete Camera;
		Camera = NULL;

		delete AssetMgr;
		AssetMgr = NULL;

		delete GameObjectMgr;
		GameObjectMgr = NULL;

		SDL_DestroyRenderer(Renderer);
		Renderer = NULL;

		SDL_DestroyWindow(m_window);
		m_window = NULL;

		Mix_Quit();
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	void Engine::GameLoop()
	{
		Uint32 ticksLastFrame = SDL_GetTicks();
		while (m_running)
		{
			//TODO: move to a function
			while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_LENGTH));
			m_deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.f;
			if (m_deltaTime > 0.1f) m_deltaTime = 0.1f;

			ProcessInput();

			HandleGameEvents();

			Update();

			Render();
		}
	}

	void Engine::ProcessInput()
	{
		InputMgr->Update();
	}

	void Engine::HandleGameEvents()
	{
		for (auto event : InputMgr->GetEvents())
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
			{
				m_running = false;
			}
		}
	}

	void Engine::Update()
	{
		GameObjectMgr->Update(m_deltaTime);
	}

	void Engine::Render()
	{
		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(Renderer);

		//arena->Draw(secs);
		GameObjectMgr->Render();

		SDL_RenderPresent(Renderer);
	}
}