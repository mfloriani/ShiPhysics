#include "CannonScript.h"
#include "../engine/GameObject.h"
#include "../engine/Engine.h"
#include "../engine/GameObjectManager.h"
#include "../engine/TransformComponent.h"
#include "../engine/SpriteComponent.h"
#include "../engine/RigidbodyComponent.h"
#include "../engine/BoxColliderComponent.h"
#include "../lib/glm/gtx/rotate_vector.hpp"
#include "ProjectileScript.h"

void CannonScript::Init() 
{
	m_transform = ecs::Engine::GameObjectMgr->Get(m_owner)->GetComponent<ecs::TransformComponent>();
}

void CannonScript::Update(float dt) 
{
	m_cooldown -= dt;
}

void CannonScript::Render() {}

void CannonScript::Shoot()
{
	if (m_cooldown > 0) return;

	//TODO: 1) load values from file
	//		2) move the object creation to a proper place

	ecs::GameObject* projectile = ecs::Engine::GameObjectMgr->Instantiate();
	projectile->Parent(m_owner);
	projectile->AddComponent<ecs::TransformComponent>(m_transform->m_position, m_transform->m_direction, 0.f);
	projectile->AddComponent<ecs::SpriteComponent>("bullet1");
	projectile->AddComponent<ecs::BoxColliderComponent>(0, 0, 10, 10);
	glm::vec2 force = glm::rotate(glm::vec2(1, 0) * 50000.f, m_transform->m_angle);
	projectile->AddComponent<ecs::RigidbodyComponent>(1.f, 1000.f)->AddForce(force);
	projectile->AddComponent<ProjectileScript>();

	//TODO: handle shooting sound

	m_cooldown = m_rateOfFire;
}