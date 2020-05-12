#ifndef __MISSILE_LAUNCHER_H__
#define __MISSILE_LAUNCHER_H__

#include "../engine/Component.h"

class MissileLauncher : public ecs::Component
{
public:
	MissileLauncher(float rateOfFire) :
		m_rateOfFire(rateOfFire),
		m_cooldown(0)
	{}

	virtual ~MissileLauncher() {}
	
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

private:
	ecs::TransformComponent*	m_transform;
	float						m_rateOfFire; //TODO: create weapon class to handle cooldown
	float						m_cooldown;
};

#endif // !__MISSILE_LAUNCHER_H__