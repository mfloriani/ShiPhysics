#include "FlareLauncherScript.h"
#include "../engine/GameObject.h"
#include "../engine/Engine.h"
#include "../engine/GameObjectManager.h"
#include "../engine/TransformComponent.h"
#include "../engine/SpriteComponent.h"
#include "../engine/BoxColliderComponent.h"

void FlareLauncherScript::Init()
{
	m_transform = ecs::Engine::GameObjectMgr->Get(m_owner)->GetComponent<ecs::TransformComponent>();
}

void FlareLauncherScript::Update(float dt)
{
	m_cooldown -= dt;
}

void FlareLauncherScript::Render() {}

void FlareLauncherScript::Launch()
{
	if (m_cooldown > 0) return;

	ecs::GameObject* flare = ecs::Engine::GameObjectMgr->Instantiate();
	flare->AddComponent<ecs::TransformComponent>(m_transform->m_position, m_transform->m_direction, 0.f);
	flare->AddComponent<ecs::SpriteComponent>("flare");
	flare->AddComponent<ecs::BoxColliderComponent>(0, 0, 10, 10);
	//glm::vec2 force = glm::rotate(glm::vec2(1, 0) * 20.f, m_transform->m_angle);
	//flare->AddComponent<ecs::RigidbodyComponent>()->AddForce(force);

	//TODO: handle sound

	m_cooldown = m_rateOfFire;
}