#include "HealthScript.h"
#include "../engine/Engine.h"
#include "../engine/EventSystem.h"
#include "../engine/CollisionEvent.h"
#include "../engine/DestroyEvent.h"
#include "../engine/GameObjectManager.h"

HealthScript::~HealthScript() 
{
	
}

void HealthScript::Init()
{
	ecs::Engine::EventSys->Subscribe(this, &HealthScript::OnCollisionEvent);
}

void HealthScript::OnCollisionEvent(ecs::CollisionEvent* e)
{
	SDL_Log("collision %i", m_health);
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