#include "AsteroidScript.h"
#include "../engine/GameObject.h"

void AsteroidScript::Init() 
{
	m_transform = m_owner->GetComponent<ecs::TransformComponent>();
}

void AsteroidScript::Update(float dt) 
{
	m_transform->m_angle += 0.01f * dt;
}

void AsteroidScript::Render() 
{

}