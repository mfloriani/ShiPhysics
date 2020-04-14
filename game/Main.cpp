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

Arena* arena = nullptr;
ecs::Engine* engine = new ecs::Engine;

void Shutdown()
{
	arena = NULL;
	explosionAnim = NULL;
}

void CreateArena()
{
	Ship* player1 = new Player1(
		engine->AssetMgr->GetTexture("ship1"),
		engine->AssetMgr->GetTexture("bullet1"),
		engine->AssetMgr->GetSound("shot1"),
		engine->AssetMgr->GetSound("missile1"),
		engine->AssetMgr->GetSound("explosion1"),
		engine->AssetMgr->GetTexture("missile"),
		engine->AssetMgr->GetTexture("flare"),
		explosionAnim);

	Ship* player2 = new Player2(
		engine->AssetMgr->GetTexture("ship2"),
		engine->AssetMgr->GetTexture("bullet1"),
		engine->AssetMgr->GetSound("shot1"),
		engine->AssetMgr->GetSound("missile1"),
		engine->AssetMgr->GetSound("explosion1"),
		engine->AssetMgr->GetTexture("missile"),
		engine->AssetMgr->GetTexture("flare"),
		explosionAnim);

	arena = new Arena(
		player1,
		player2,
		engine->AssetMgr->GetTexture("asteroid"),
		engine->AssetMgr->GetSound("explosion1"),
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

	if (!engine->AssetMgr->AddMusic("battle2", "./assets/Battle2.mp3")) return false;
	if (!engine->AssetMgr->AddSound("shot1", "./assets/shot1.wav")) return false;
	if (!engine->AssetMgr->AddSound("explosion1", "./assets/explosion1.wav")) return false;
	if (!engine->AssetMgr->AddSound("missile1", "./assets/missile1.wav")) return false;

	ecs::Engine::AssetMgr->AddFont("arial", "./assets/arial.ttf", 18);

	CreateArena();
	
	engine->AssetMgr->PlayMusic("battle2");

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
