#include "ExplosionScript.h"
#include "../engine/Engine.h"
#include "../engine/GameObjectManager.h"
#include "../engine/GameObject.h"
#include "../engine/EventSystem.h"
#include "../engine/TransformComponent.h"
#include "../engine/SpriteComponent.h"
#include "../engine/AnimationComponent.h"
#include "../engine/DestroyEvent.h"
#include "../engine/AudioSystem.h"

void ExplosionScript::Init()
{
	m_transform = ecs::Engine::GameObjectMgr->Get(m_owner)->GetComponent<ecs::TransformComponent>();
	ecs::Engine::EventSys->Subscribe(this, &ExplosionScript::OnDestroyEvent);
}

void ExplosionScript::Update(float dt)
{

}

void ExplosionScript::Render()
{

}

void ExplosionScript::OnDestroyEvent(ecs::DestroyEvent* e)
{
	if (m_owner != e->m_gameObjectId) return;
	SDL_Log("Destroy event caught %i", e->m_gameObjectId);

	//TODO: create a factory or something
	ecs::GameObject* explosion = ecs::Engine::GameObjectMgr->Instantiate();
	explosion->AddComponent<ecs::TransformComponent>(m_transform->m_position, glm::vec2(0, 0), 0.f);
	explosion->AddComponent<ecs::SpriteComponent>("explosion_spritesheet");
	explosion->AddComponent<ecs::AnimationComponent>("explosion");

	//TODO: should be an audio component? How to handle this?
	ecs::Engine::AudioSys->PlaySound("explosion1", 10);
}