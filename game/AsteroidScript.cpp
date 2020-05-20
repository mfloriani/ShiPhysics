#include "AsteroidScript.h"
#include "../engine/TransformComponent.h"
#include "../engine/Engine.h"
#include "../engine/GameObject.h"
#include "../engine/GameObjectManager.h"

void AsteroidScript::Init() 
{
	m_transform = ecs::Engine::GameObjectMgr->Get(m_owner)->GetComponent<ecs::TransformComponent>();

}

void AsteroidScript::Update(float dt) 
{
	m_transform->m_angle += 1.f * dt;
}

void AsteroidScript::Render() 
{

}