#include "HealthScript.h"
#include "../engine/Engine.h"
#include "../engine/EventSystem.h"
#include "../engine/CollisionEvent.h"
#include "../engine/DestroyEvent.h"
#include "../engine/GameObjectManager.h"
#include "../engine/GameObject.h"

HealthScript::~HealthScript() 
{
	
}

void HealthScript::Init()
{
	ecs::Engine::EventSys->Subscribe(this, &HealthScript::OnCollisionEvent);
}

void HealthScript::OnCollisionEvent(ecs::CollisionEvent* e)
{
	
	if (e->m_leftGameObjectId != m_owner && e->m_rightGameObjectId != m_owner) return;

	SDL_Log("collision - current health %i", m_health);
	if (m_health <= 0) return;
	
	m_health -= 10;
	if (m_health <= 0)
	{
		SDL_Log("destroy");
		ecs::Engine::EventSys->Publish(new ecs::DestroyEvent(m_owner));
		ecs::Engine::GameObjectMgr->Destroy(m_owner);
	}
}

void HealthScript::Update(float dt)
{
	
}

void HealthScript::Render()
{

}