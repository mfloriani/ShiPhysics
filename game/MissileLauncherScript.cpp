#include "MissileLauncherScript.h"
#include "../engine/GameObject.h"
#include "../engine/Engine.h"
#include "../engine/GameObjectManager.h"
#include "../engine/TransformComponent.h"
#include "../engine/SpriteComponent.h"
#include "../engine/RigidbodyComponent.h"
#include "../engine/BoxColliderComponent.h"
#include "../lib/glm/gtx/rotate_vector.hpp"

void MissileLauncherScript::Init() 
{
	m_transform = m_owner->GetComponent<ecs::TransformComponent>();
}

void MissileLauncherScript::Update(float dt) 
{
	m_cooldown -= dt;
}

void MissileLauncherScript::Render() {}

void MissileLauncherScript::Launch()
{
	if (m_cooldown > 0) return;

	//TODO: load values from file

	ecs::GameObject* missile = ecs::Engine::GameObjectMgr->NewGameObject();
	missile->AddComponent<ecs::TransformComponent>(m_transform->m_position, m_transform->m_direction, 0.f);
	missile->AddComponent<ecs::SpriteComponent>("missile");
	missile->AddComponent<ecs::BoxColliderComponent>(0, 0, 10, 10);
	glm::vec2 force = glm::rotate(glm::vec2(1, 0) * 50000.f, m_transform->m_angle);
	missile->AddComponent<ecs::RigidbodyComponent>(1.f, 5000.f)->AddForce(force);

	//TODO: handle shooting sound

	m_cooldown = m_rateOfFire;
}