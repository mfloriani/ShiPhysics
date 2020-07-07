#include "ProjectileScript.h"
#include "../engine/Engine.h"
#include "../engine/EventSystem.h"
#include "../engine/CollisionEvent.h"

#include "../engine/GameObjectManager.h"
#include "../engine/GameObject.h"
#include "../engine/CollisionSystem.h"
#include "../engine/TransformComponent.h"

void ProjectileScript::Init()
{
	m_transform = ecs::Engine::GameObjectMgr->Get(m_owner)->GetComponent<ecs::TransformComponent>();
	ecs::Engine::EventSys->Subscribe(this, &ProjectileScript::OnCollisionEvent);
}

void ProjectileScript::Update(float dt)
{
	if (ecs::IsOffScreen(m_transform))
	{
		ecs::Engine::GameObjectMgr->Destroy(m_owner);
	}
}

void ProjectileScript::Render()
{
}

void ProjectileScript::OnCollisionEvent(ecs::CollisionEvent* e)
{
	if (e->m_leftGameObjectId != m_owner && e->m_rightGameObjectId != m_owner) return;

	SDL_Log("collision event handling (%i)", m_owner);		
	ecs::Engine::GameObjectMgr->Destroy(m_owner);
}