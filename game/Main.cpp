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
#include "../engine/SteeringComponent.h"
#include "../engine/GameObjectManager.h"
#include "../engine/PhysicsSystem.h"
#include "../engine/AnimationComponent.h"
#include "../engine/TextComponent.h"
#include "Player1Controller.h"
#include "Cannon.h"
#include "MissileLauncher.h"
#include "FlareLauncher.h"
#include "AsteroidScript.h"
#include "FPSScript.h"

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

	//TODO: read this from a file
	std::vector<SDL_Rect> explosionClips{
		{0,0,60,59},
		{60,0,60,59},
		{120,0,60,59},
		{180,0,60,59},
		{240,0,60,59}
	};
	
	if (!engine->AssetMgr->AddMusic("battle2", "./assets/Battle2.mp3")) return false;
	if (!engine->AssetMgr->AddSound("shot1", "./assets/shot1.wav")) return false;
	if (!engine->AssetMgr->AddSound("explosion1", "./assets/explosion1.wav")) return false;
	if (!engine->AssetMgr->AddSound("missile1", "./assets/missile1.wav")) return false;

	ecs::Engine::AssetMgr->AddFont("arial", "./assets/arial.ttf", 18);

	//engine->AssetMgr->PlayMusic("battle2");

	//TODO: load gameobjects from file

	ecs::GameObject* player1 = engine->GameObjectMgr->NewGameObject();
	player1->AddComponent<ecs::TransformComponent>(glm::vec2(10, 10), glm::vec2(0, 0), 0.f);
	player1->AddComponent<ecs::SpriteComponent>("ship1");
	//player1->AddComponent<ecs::BoxColliderComponent>(0, 0, 32, 32);	
	player1->AddComponent<ecs::RigidbodyComponent>(1.f, 200.f);
	//player1->AddComponent<Cannon>(3.f); //TODO: solve inter dependencies between components
	//player1->AddComponent<MissileLauncher>(5.f); //TODO: solve inter dependencies between components
	player1->AddComponent<Player1Controller>();
	
	//ecs::GameObject* player2 = engine->GameObjectMgr->NewGameObject();
	//player2->AddComponent<ecs::TransformComponent>(glm::vec2(500, 500), glm::vec2(0, 0), 0.f);
	//player2->AddComponent<ecs::SpriteComponent>("ship2");
	//player2->AddComponent<ecs::BoxColliderComponent>(0, 0, 32, 32);
	//player2->AddComponent<ecs::RigidbodyComponent>(1.f, 1.f);
	//player2->AddComponent<FlareLauncher>(1.f);
	//player2->AddComponent<Player1Controller>();

	//ecs::GameObject* asteroid = engine->GameObjectMgr->NewGameObject();
	//asteroid->AddComponent<ecs::TransformComponent>(glm::vec2(1400, 300), glm::vec2(0, 0), 0.f);
	//asteroid->AddComponent<ecs::SpriteComponent>("asteroid");
	//glm::vec2 force{ -10000,0 };
	//asteroid->AddComponent<ecs::RigidbodyComponent>(1.f, 100.f)->AddForce(force);
	//asteroid->AddComponent<ecs::BoxColliderComponent>(0, 0, 60, 60);
	//ecs::SteeringComponent* steering = asteroid->AddComponent<ecs::SteeringComponent>();
	//steering->SetTarget(player1);
	//auto current = steering->Enable(ecs::BehaviorsType::Pursuit);
	//asteroid->AddComponent<AsteroidScript>();

	//ecs::SteeringComponent* steering2 = player2->AddComponent<ecs::SteeringComponent>();
	//steering2->SetTarget(asteroid);
	//steering2->Enable(ecs::BehaviorsType::Flee);

	//TODO: create explosion when asteroids and ships explode
	//ecs::GameObject* explosion = engine->GameObjectMgr->NewGameObject();
	//explosion->AddComponent<ecs::TransformComponent>(glm::vec2(100, 100), glm::vec2(0, 0), 0.f);
	//explosion->AddComponent<ecs::SpriteComponent>("explosion_spritesheet");
	//explosion->AddComponent<ecs::AnimationComponent>(explosionClips, 200, false);

	ecs::GameObject* fps = engine->GameObjectMgr->NewGameObject();
	fps->AddComponent<ecs::TransformComponent>(glm::vec2(0, 0), glm::vec2(0, 0), 0.f);
	SDL_Color gray{ 0, 100, 100, 100 };
	fps->AddComponent<ecs::TextComponent>("FPS", "arial", gray);
	fps->AddComponent<FPSScript>();

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
