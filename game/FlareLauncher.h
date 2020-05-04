#ifndef __FLARE_LAUNCHER_H__
#define __FLARE_LAUNCHER_H__

#include "../engine/Component.h"

class FlareLauncher : public ecs::Component
{
public:
	FlareLauncher(float rateOfFire) :
		m_rateOfFire(rateOfFire),
		m_cooldown(0)
	{}

	virtual ~FlareLauncher() {}

	virtual void Init() override
	{
		m_transform = m_owner->GetComponent<ecs::TransformComponent>();
	}

	virtual void Update(float dt) override 
	{
		m_cooldown -= dt;
	}

	virtual void Render() override {}

	void Launch()
	{
		if (m_cooldown > 0) return;

		ecs::GameObject* flare = ecs::Engine::GameObjectMgr->NewGameObject();
		flare->AddComponent<ecs::TransformComponent>(m_transform->m_position, m_transform->m_direction, 0.f);
		flare->AddComponent<ecs::SpriteComponent>("flare");
		flare->AddComponent<ecs::BoxColliderComponent>(0, 0, 10, 10);
		//glm::vec2 force = glm::rotate(glm::vec2(1, 0) * 20.f, m_transform->m_angle);
		//flare->AddComponent<ecs::RigidbodyComponent>()->AddForce(force);
		//TODO: handle sound

		m_cooldown = m_rateOfFire;
	}

private:
	ecs::TransformComponent*	m_transform;
	float						m_rateOfFire; //TODO: create weapon class to handle cooldown
	float						m_cooldown;
};

#endif // !__FLARE_LAUNCHER_H__