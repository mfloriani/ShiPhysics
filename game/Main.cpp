#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "../engine/GameObject.h"
#include "../engine/Timer.h"
#include "../engine/Animation.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Player1.h"
#include "Player2.h"
#include "Arena.h"
#include "../engine/AssetManager.h"
#include "../engine/Engine.h"

Timer fpsTimer;
int countedFrames = 0;

Animation* explosionAnim = NULL;

const int EXPLOSION_ANIM_FRAMES = 5;
SDL_Rect gExplosionClips[EXPLOSION_ANIM_FRAMES];

Mix_Music* gMusic;
Mix_Chunk* gShot;
Mix_Chunk* gExplosion;
Mix_Chunk* gMissile;

Arena* arena = nullptr;
ecs::Engine* engine = new ecs::Engine;

//bool Initialize()
//{
//	
//
//	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
//	{
//		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//		return false;
//	}
//	gWindow = SDL_CreateWindow("ShiPhysics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//	if (gWindow == NULL)
//	{
//		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
//		return false;
//	}
//	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//	if (gRenderer == NULL)
//	{
//		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
//		return false;
//	}
//	int imgFlags = IMG_INIT_PNG;
//	if (!(IMG_Init(imgFlags)&imgFlags))
//	{
//		printf("SDL_image cound not initialize! SDL_Image Error: %s\n", IMG_GetError());
//		return false;
//	}
//	if (TTF_Init() == -1)
//	{
//		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
//		return false;
//	}
//	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
//	{
//		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
//		return false;
//	}
//
//	return true;
//}

void Shutdown()
{
	arena = NULL;

	Mix_FreeChunk(gShot);
	Mix_FreeChunk(gExplosion);
	Mix_FreeChunk(gMissile);
	gShot = NULL;
	gExplosion = NULL;
	gMissile = NULL;

	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	explosionAnim = NULL;
}

void CreateArena()
{
	Ship* player1 = new Player1(
		engine->AssetMgr->GetTexture("ship1"),
		engine->AssetMgr->GetTexture("bullet1"),
		gShot,
		gMissile,
		gExplosion,
		engine->AssetMgr->GetTexture("missile"),
		engine->AssetMgr->GetTexture("flare"),
		explosionAnim);

	Ship* player2 = new Player2(
		engine->AssetMgr->GetTexture("ship2"),
		engine->AssetMgr->GetTexture("bullet1"),
		gShot,
		gMissile,
		gExplosion,
		engine->AssetMgr->GetTexture("missile"),
		engine->AssetMgr->GetTexture("flare"),
		explosionAnim);

	arena = new Arena(
		player1,
		player2,
		engine->AssetMgr->GetTexture("asteroid"),
		gExplosion,
		explosionAnim);
}

bool Load()
{
	if (!engine->AssetMgr->AddTexture("ship1", "./assets/ship1.png")) return false;
	if (!engine->AssetMgr->AddTexture("ship2", "./assets/ship2.png")) return false;
	if (!engine->AssetMgr->AddTexture("bullet1", "./assets/bullet1.png")) return false;
	if (!engine->AssetMgr->AddTexture("missile", "./assets/missile.png")) return false;
	if (!engine->AssetMgr->AddTexture("asteroid", "./assets/asteroid.png")) return false;
	if (!engine->AssetMgr->AddTexture("flare", "./assets/flare.png")) return false;
	if (!engine->AssetMgr->AddTexture("explosion_spritesheet", "./assets/explosion_spritesheet.png")) return false;

	gExplosionClips[0].x = 0;
	gExplosionClips[0].y = 0;
	gExplosionClips[0].w = 60;
	gExplosionClips[0].h = 59;

	gExplosionClips[1].x = 60;
	gExplosionClips[1].y = 0;
	gExplosionClips[1].w = 60;
	gExplosionClips[1].h = 59;

	gExplosionClips[2].x = 120;
	gExplosionClips[2].y = 0;
	gExplosionClips[2].w = 60;
	gExplosionClips[2].h = 59;

	gExplosionClips[3].x = 180;
	gExplosionClips[3].y = 0;
	gExplosionClips[3].w = 60;
	gExplosionClips[3].h = 59;

	gExplosionClips[4].x = 240;
	gExplosionClips[4].y = 0;
	gExplosionClips[4].w = 60;
	gExplosionClips[4].h = 59;

	explosionAnim = new Animation(engine->AssetMgr->GetTexture("explosion_spritesheet"), 5, gExplosionClips);

	gMusic = Mix_LoadMUS("./assets/Battle2.mp3");
	if (gMusic == NULL)
	{
		printf("Failed to load Battle2.mp3! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}


	gShot = Mix_LoadWAV("./assets/shot1.wav");
	if (gShot == NULL)
	{
		printf("Failed to load shot1.wav! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}


	gExplosion = Mix_LoadWAV("./assets/explosion1.wav");
	if (gExplosion == NULL)
	{
		printf("Failed to load explosion1.wav! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	gMissile = Mix_LoadWAV("./assets/missile1.wav");
	if (gMissile == NULL)
	{
		printf("Failed to load missile1.wav! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}


	ecs::Engine::AssetMgr->AddFont("arial", "./assets/arial.ttf", 18);

	Mix_VolumeMusic(20);
	Mix_VolumeChunk(gMissile, 20);
	Mix_VolumeChunk(gShot, 20);
	// Mix_VolumeChunk(gExplosion, 20);

	CreateArena();

	return true;
}

int main(int argc, char* args[])
{
	srand((unsigned int)time(NULL));

	if (!engine->Init())
	{
		engine->Quit();
		return 1;
	}

	if (!Load())
	{
		engine->Quit();
		return 1;
	}

	bool quit = false;
	SDL_Event evt;
	fpsTimer.start();
	Uint32 before = SDL_GetTicks();
	Uint32 now = 0;
	Mix_PlayMusic(gMusic, -1);

	while (!quit)
	{
		now = SDL_GetTicks() - before;
		before = SDL_GetTicks();
		float secs = now / 1000.0f;

		while (SDL_PollEvent(&evt) != 0)
		{
			if (evt.type == SDL_QUIT || (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE))
			{
				quit = true;
			}
			else if (evt.type == SDL_KEYDOWN)
			{
				switch (evt.key.keysym.sym)
				{
				case SDLK_RETURN:
					CreateArena();
					break;
				}
			}
			arena->Input(&evt);
		}
		arena->Update(secs);

		SDL_SetRenderDrawColor(engine->Renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(engine->Renderer);
		arena->Draw(secs);

		SDL_RenderPresent(engine->Renderer);
		++countedFrames;
	}


	Shutdown();

	engine->Quit();

	return 0;
}
