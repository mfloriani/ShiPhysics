#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "../engine/GameObject.h"
#include "../engine/AssetManager.h"
#include "../engine/Engine.h"
#include "../engine/TransformComponent.h"
#include "../engine/SpriteComponent.h"
#include "../engine/RigidbodyComponent.h"
#include "../engine/BoxColliderComponent.h"
#include "Player1Controller.h"
#include "Cannon.h"
#include "MissileLauncher.h"
#include "FlareLauncher.h"

//Animation* explosionAnim = NULL;
//const int EXPLOSION_ANIM_FRAMES = 5;
//SDL_Rect gExplosionClips[EXPLOSION_ANIM_FRAMES];

ecs::Engine* engine = new ecs::Engine;

bool Load()
{
	if (!engine->AssetMgr->AddTexture("ship1", "./assets/ship1.png")) return false;
	if (!engine->AssetMgr->AddTexture("ship2", "./assets/ship2.png")) return false;
	if (!engine->AssetMgr->AddTexture("bullet1", "./assets/bullet1.png")) return false;
	if (!engine->AssetMgr->AddTexture("missile", "./assets/missile.png")) return false;
	if (!engine->AssetMgr->AddTexture("asteroid", "./assets/asteroid.png")) return false;
	if (!engine->AssetMgr->AddTexture("flare", "./assets/flare.png")) return false;
	if (!engine->AssetMgr->AddTexture("explosion_spritesheet", "./assets/explosion_spritesheet.png")) return false;

	//gExplosionClips[0].x = 0;
	//gExplosionClips[0].y = 0;
	//gExplosionClips[0].w = 60;
	//gExplosionClips[0].h = 59;

	//gExplosionClips[1].x = 60;
	//gExplosionClips[1].y = 0;
	//gExplosionClips[1].w = 60;
	//gExplosionClips[1].h = 59;

	//gExplosionClips[2].x = 120;
	//gExplosionClips[2].y = 0;
	//gExplosionClips[2].w = 60;
	//gExplosionClips[2].h = 59;

	//gExplosionClips[3].x = 180;
	//gExplosionClips[3].y = 0;
	//gExplosionClips[3].w = 60;
	//gExplosionClips[3].h = 59;

	//gExplosionClips[4].x = 240;
	//gExplosionClips[4].y = 0;
	//gExplosionClips[4].w = 60;
	//gExplosionClips[4].h = 59;

	//explosionAnim = new Animation(engine->AssetMgr->GetTexture("explosion_spritesheet"), 5, gExplosionClips);

	if (!engine->AssetMgr->AddMusic("battle2", "./assets/Battle2.mp3")) return false;
	if (!engine->AssetMgr->AddSound("shot1", "./assets/shot1.wav")) return false;
	if (!engine->AssetMgr->AddSound("explosion1", "./assets/explosion1.wav")) return false;
	if (!engine->AssetMgr->AddSound("missile1", "./assets/missile1.wav")) return false;

	ecs::Engine::AssetMgr->AddFont("arial", "./assets/arial.ttf", 18);

	engine->AssetMgr->PlayMusic("battle2");

	ecs::GameObject* player1 = engine->GameObjectMgr->AddGameObject();
	player1->AddComponent<ecs::TransformComponent>(glm::vec2(10,10), glm::vec2(0,0), 0.f);
	player1->AddComponent<ecs::SpriteComponent>("ship1");
	player1->AddComponent<ecs::BoxColliderComponent>(0, 0, 32, 32);
	player1->AddComponent<ecs::RigidbodyComponent>();
	player1->AddComponent<Cannon>(); //TODO: solve inter dependencies between components
	player1->AddComponent<MissileLauncher>(); //TODO: solve inter dependencies between components
	player1->AddComponent<Player1Controller>();

	ecs::GameObject* player2 = engine->GameObjectMgr->AddGameObject();
	player2->AddComponent<ecs::TransformComponent>(glm::vec2(100, 100), glm::vec2(0, 0), 0.f);
	player2->AddComponent<ecs::SpriteComponent>("ship2");
	player2->AddComponent<ecs::BoxColliderComponent>(0, 0, 32, 32);
	player2->AddComponent<ecs::RigidbodyComponent>();
	player2->AddComponent<FlareLauncher>();
	player2->AddComponent<Player1Controller>();

	ecs::GameObject* asteroid = engine->GameObjectMgr->AddGameObject();
	asteroid->AddComponent<ecs::TransformComponent>(glm::vec2(500, 500), glm::vec2(20, 20), 0.f);
	asteroid->AddComponent<ecs::SpriteComponent>("asteroid");

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

	engine->GameLoop();
	engine->Quit();

	return 0;
}
