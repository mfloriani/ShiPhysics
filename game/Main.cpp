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
#include "../engine/AudioSystem.h"
#include "Player1Script.h"
#include "CannonScript.h"
#include "MissileLauncherScript.h"
#include "FlareLauncherScript.h"
#include "AsteroidScript.h"
#include "FPSScript.h"
#include "HealthScript.h"
#include "ExplosionScript.h"

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
	engine->AssetMgr->AddAnimation("explosion", explosionClips, 200, false);
	
	if (!engine->AssetMgr->AddMusic("battle2", "./assets/Battle2.mp3")) return false;
	if (!engine->AssetMgr->AddSound("shot1", "./assets/shot1.wav")) return false;
	if (!engine->AssetMgr->AddSound("explosion1", "./assets/explosion1.wav")) return false;
	if (!engine->AssetMgr->AddSound("missile1", "./assets/missile1.wav")) return false;

	ecs::Engine::AssetMgr->AddFont("arial", "./assets/arial.ttf", 18);

	engine->AudioSys->PlayMusic("battle2");
	engine->AudioSys->ToggleMusic();


	//TODO: load gameobjects from file

	ecs::GameObject* player1 = engine->GameObjectMgr->Instantiate();
	player1->AddComponent<ecs::TransformComponent>(glm::vec2(10, 10), glm::vec2(0, 0), 0.f);
	player1->AddComponent<ecs::SpriteComponent>("ship1");
	player1->AddComponent<ecs::BoxColliderComponent>(0, 0, 32, 32);	
	player1->AddComponent<ecs::RigidbodyComponent>(1.f, 200.f);
	player1->AddComponent<CannonScript>(1.f); //TODO: solve inter dependencies between components
	player1->AddComponent<MissileLauncherScript>(3.f); //TODO: solve inter dependencies between components
	player1->AddComponent<Player1Script>();
	//player1->AddComponent<HealthScript>(100);
	
	ecs::GameObject* player2 = engine->GameObjectMgr->Instantiate();
	player2->AddComponent<ecs::TransformComponent>(glm::vec2(500, 500), glm::vec2(0, 0), 0.f);
	player2->AddComponent<ecs::SpriteComponent>("ship2");
	player2->AddComponent<ecs::BoxColliderComponent>(0, 0, 32, 32);
	player2->AddComponent<ecs::RigidbodyComponent>(1.f, 100.f);
	player2->AddComponent<FlareLauncherScript>(1.f);
	//player2->AddComponent<Player1Script>();
	player2->AddComponent<HealthScript>(100);
	player2->AddComponent<ExplosionScript>();

	ecs::GameObject* asteroid = engine->GameObjectMgr->Instantiate();
	asteroid->AddComponent<ecs::TransformComponent>(glm::vec2(1400, 300), glm::vec2(0, 0), 0.f);
	asteroid->AddComponent<ecs::SpriteComponent>("asteroid");
	glm::vec2 force{ -100,0 };
	asteroid->AddComponent<ecs::RigidbodyComponent>(1.f, 100.f)->AddForce(force);
	asteroid->AddComponent<ecs::BoxColliderComponent>(0, 0, 60, 60);
	//ecs::SteeringComponent* steering = asteroid->AddComponent<ecs::SteeringComponent>();
	//steering->SetTarget(player1->Id());
	//auto current = steering->Enable(ecs::BehaviorsType::Pursuit);
	asteroid->AddComponent<AsteroidScript>();
	asteroid->AddComponent<HealthScript>(20);
	asteroid->AddComponent<ExplosionScript>();

	//ecs::SteeringComponent* steering2 = player2->AddComponent<ecs::SteeringComponent>();
	//steering2->SetTarget(asteroid->Id());
	//steering2->Enable(ecs::BehaviorsType::Flee);

	{
		ecs::GameObject* asteroid = engine->GameObjectMgr->Instantiate();
		asteroid->AddComponent<ecs::TransformComponent>(glm::vec2(1400, 400), glm::vec2(0, 0), 0.f);
		asteroid->AddComponent<ecs::SpriteComponent>("asteroid");
		glm::vec2 force{ -100,0 };
		asteroid->AddComponent<ecs::RigidbodyComponent>(1.f, 100.f)->AddForce(force);
		asteroid->AddComponent<ecs::BoxColliderComponent>(0, 0, 60, 60);
		//ecs::SteeringComponent* steering = asteroid->AddComponent<ecs::SteeringComponent>();
		//steering->SetTarget(player1->Id());
		//auto current = steering->Enable(ecs::BehaviorsType::Pursuit);
		asteroid->AddComponent<AsteroidScript>();
		asteroid->AddComponent<HealthScript>(20);
		asteroid->AddComponent<ExplosionScript>();
	}
	
	{
		ecs::GameObject* asteroid = engine->GameObjectMgr->Instantiate();
		asteroid->AddComponent<ecs::TransformComponent>(glm::vec2(1400, 600), glm::vec2(0, 0), 0.f);
		asteroid->AddComponent<ecs::SpriteComponent>("asteroid");
		glm::vec2 force{ -100,0 };
		asteroid->AddComponent<ecs::RigidbodyComponent>(1.f, 100.f)->AddForce(force);
		asteroid->AddComponent<ecs::BoxColliderComponent>(0, 0, 60, 60);
		//ecs::SteeringComponent* steering = asteroid->AddComponent<ecs::SteeringComponent>();
		//steering->SetTarget(player1->Id());
		//auto current = steering->Enable(ecs::BehaviorsType::Pursuit);
		asteroid->AddComponent<AsteroidScript>();
		asteroid->AddComponent<HealthScript>(20);
		asteroid->AddComponent<ExplosionScript>();
	}

	ecs::GameObject* fps = engine->GameObjectMgr->Instantiate();
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
