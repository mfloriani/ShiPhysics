#include "FlareLauncherScript.h"
#include "../engine/GameObject.h"
#include "../engine/Engine.h"
#include "../engine/GameObjectManager.h"
#include "../engine/TransformComponent.h"
#include "../engine/SpriteComponent.h"
#include "../engine/BoxColliderComponent.h"
#include "../engine/AudioSystem.h"
#include "ProjectileScript.h"

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
	flare->Parent(m_owner);
	flare->AddComponent<ecs::TransformComponent>(m_transform->m_position, m_transform->m_direction, 0.f);
	flare->AddComponent<ecs::SpriteComponent>("flare");
	flare->AddComponent<ecs::BoxColliderComponent>(0, 0, 10, 10);
	flare->AddComponent<ProjectileScript>();
	//glm::vec2 force = glm::rotate(glm::vec2(1, 0) * 20.f, m_transform->m_angle);
	//flare->AddComponent<ecs::RigidbodyComponent>()->AddForce(force);

	//TODO: should be an audio component? How to handle this?
	ecs::Engine::AudioSys->PlaySound("missile1", 10);

	m_cooldown = m_rateOfFire;
}