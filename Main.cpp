#include <stdio.h>
#include <string>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Ship.h"
#include "Texture.h"
#include "Timer.h"
#include "Vector2D.h"
#include <vector>
#include "GameObject.h"
#include "Asteroid.h"
#include "Player1.h"
#include "Player2.h"
#include "Arena.h"
#include "Config.h"
#include "Animation.h"

using namespace std;

SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont = NULL;

Timer fpsTimer;
int countedFrames = 0;
Texture ship1Texture;
Texture ship2Texture;
Texture bullet1Texture;
Texture missileTexture;
Texture asteroidTexture;
Texture flareTexture;
Texture explosionTexture;

Animation* explosionAnim = NULL;

const int EXPLOSION_ANIM_FRAMES = 5;
SDL_Rect gExplosionClips[EXPLOSION_ANIM_FRAMES];


Mix_Music* gMusic;
Mix_Chunk* gShot;
Mix_Chunk* gExplosion;
Mix_Chunk* gMissile;

Arena* arena = nullptr;


bool Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	gWindow = SDL_CreateWindow("ShiPhysics", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == NULL)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags)&imgFlags))
	{
		printf("SDL_image cound not initialize! SDL_Image Error: %s\n", IMG_GetError());
		return false;
	}
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	return true;
}

void Shutdown()
{
	ship1Texture.Free();
	ship2Texture.Free();
	bullet1Texture.Free();
	missileTexture.Free();
	asteroidTexture.Free();
	flareTexture.Free();
	explosionTexture.Free();

	arena = NULL;
	
	TTF_CloseFont(gFont);
	gFont = NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	Mix_FreeChunk(gShot);
	Mix_FreeChunk(gExplosion);
	Mix_FreeChunk(gMissile);
	gShot = NULL;
	gExplosion = NULL;
	gMissile = NULL;

	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	
	explosionAnim = NULL;

	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void CreateArena()
{
	Ship* player1 = new Player1(&ship1Texture, &bullet1Texture, gShot, gMissile, gExplosion, &missileTexture, &flareTexture, explosionAnim);
	Ship* player2 = new Player2(&ship2Texture, &bullet1Texture, gShot, gMissile, gExplosion, &missileTexture, &flareTexture, explosionAnim);

	arena = new Arena(player1, player2, &asteroidTexture, &camera, gExplosion, gFont, gRenderer, explosionAnim);
}

bool Load()
{
	if (!ship1Texture.LoadFromFile(gRenderer, "ship1.png"))
		return false;
	if (!ship2Texture.LoadFromFile(gRenderer, "ship2.png"))
		return false;
	if (!bullet1Texture.LoadFromFile(gRenderer, "bullet1.png"))
		return false;
	if (!missileTexture.LoadFromFile(gRenderer, "missile.png"))
		return false;
	if (!asteroidTexture.LoadFromFile(gRenderer, "asteroid.png"))
		return false;
	if (!flareTexture.LoadFromFile(gRenderer, "flare.png"))
		return false;
	if (!explosionTexture.LoadFromFile(gRenderer, "explosion_spritesheet.png"))
		return false;

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

	explosionAnim = new Animation(&explosionTexture, 5, gExplosionClips);

	gMusic = Mix_LoadMUS("Battle2.mp3");
	if (gMusic == NULL)
	{
		printf("Failed to load Battle2.mp3! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	

	gShot = Mix_LoadWAV("shot1.wav");
	if (gShot == NULL)
	{
		printf("Failed to load shot1.wav! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	

	gExplosion = Mix_LoadWAV("explosion1.wav");
	if (gExplosion == NULL)
	{
		printf("Failed to load explosion1.wav! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	gMissile = Mix_LoadWAV("missile1.wav");
	if (gMissile == NULL)
	{
		printf("Failed to load missile1.wav! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	

	gFont = TTF_OpenFont("arial.ttf", 18);
	if (gFont == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	Mix_VolumeMusic(20);
	Mix_VolumeChunk(gMissile, 20);
	Mix_VolumeChunk(gShot, 20);
	// Mix_VolumeChunk(gExplosion, 20);

	CreateArena();

	return true;
}

void CalculateFPS()
{
	float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
	if (avgFPS > 2000000) avgFPS = 0;

	std::string fps;
	fps = "FPS " + std::to_string(avgFPS);
	SDL_SetWindowTitle(gWindow, fps.c_str());
}



int main(int argc, char* args[])
{
	srand(time(NULL));
	if (Initialize())
	{
		if (Load())
		{
			bool quit = false;
			SDL_Event evt;
			fpsTimer.start();
			Uint32 before = SDL_GetTicks();
			Uint32 now = 0;
			Mix_PlayMusic(gMusic,-1);

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
				CalculateFPS();
				arena->Update(secs);
				
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
				//SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0xFF);
				SDL_RenderClear(gRenderer);
				arena->Draw(secs);
				
				SDL_RenderPresent(gRenderer);
				++countedFrames;
			}
		}
	}

	Shutdown();
	return 0;
}
