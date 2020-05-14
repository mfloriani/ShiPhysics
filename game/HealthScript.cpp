#include "HealthScript.h"
#include "../engine/Engine.h"
#include "../engine/EventSystem.h"
#include "../engine/CollisionEvent.h"

void HealthScript::Init()
{
	ecs::Engine::EventSys->Subscribe(this, &HealthScript::OnCollisionEvent);
}

void HealthScript::OnCollisionEvent(ecs::CollisionEvent* e)
{
	SDL_Log("getting collision event");
}

void HealthScript::Update(float dt)
{

}

void HealthScript::Render()
{

}