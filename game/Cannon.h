#ifndef __CANNON_H__
#define __CANNON_H__

#include "../engine/Component.h"

class Cannon : public ecs::Component
{
public:
	virtual ~Cannon() {}
	virtual void Init() override
	{
		m_transform = m_owner->GetComponent<ecs::TransformComponent>();
	}
	virtual void Update(float dt) override
	{

	}
	virtual void Render() override {}

	void Shoot()
	{
		ecs::GameObject* projectile = ecs::Engine::GameObjectMgr->AddGameObject();
		projectile->AddComponent<ecs::TransformComponent>(m_transform->m_position, m_transform->m_direction, 0.f);
		projectile->AddComponent<ecs::SpriteComponent>("bullet1");
		projectile->AddComponent<ecs::BoxColliderComponent>(0, 0, 10, 10);
		glm::vec2 force = glm::rotate(glm::vec2(1, 0) * 20.f, m_transform->m_angle);
		projectile->AddComponent<ecs::RigidbodyComponent>(1.f, 10.f)->AddForce(force);
		//TODO: handle shooting sound
	}

private:
	ecs::TransformComponent* m_transform;
};

#endif // !__CANNON_H__

