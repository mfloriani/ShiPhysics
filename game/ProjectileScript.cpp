#include "ProjectileScript.h"
#include "../engine/Engine.h"
#include "../engine/EventSystem.h"
#include "../engine/CollisionEvent.h"
#include "../engine/DestroyEvent.h"
#include "../engine/GameObjectManager.h"
#include "../engine/GameObject.h"

void ProjectileScript::Init()
{
	ecs::Engine::EventSys->Subscribe(this, &ProjectileScript::OnCollisionEvent);
}

void ProjectileScript::Update(float dt)
{
}

void ProjectileScript::Render()
{
}

void ProjectileScript::OnCollisionEvent(ecs::CollisionEvent* e)
{
	if (e->m_leftGameObjectId != m_owner && e->m_rightGameObjectId != m_owner) return;

	SDL_Log("collision event handling (%i)", m_owner);
	SDL_Log("destroy event published to (%i)", m_owner);
	ecs::Engine::EventSys->Publish(new ecs::DestroyEvent(m_owner));
	ecs::Engine::GameObjectMgr->Destroy(m_owner);
}