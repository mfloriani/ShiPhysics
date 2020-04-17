#ifndef __MISSILE_LAUNCHER_H__
#define __MISSILE_LAUNCHER_H__

#include "../engine/Component.h"

class MissileLauncher : public ecs::Component
{
public:
	virtual ~MissileLauncher() {}
	virtual void Init() override 
	{
		m_transform = m_owner->GetComponent<ecs::TransformComponent>();
	}
	virtual void Update(float dt) override {}
	virtual void Render() override {}

	void Launch()
	{
		ecs::GameObject* missile = ecs::Engine::GameObjectMgr->AddGameObject();
		missile->AddComponent<ecs::TransformComponent>(m_transform->m_position, m_transform->m_direction, 0.f);
		missile->AddComponent<ecs::SpriteComponent>("missile");
		missile->AddComponent<ecs::BoxColliderComponent>(0, 0, 10, 10);
		glm::vec2 force = glm::rotate(glm::vec2(1, 0) * 20.f, m_transform->m_angle);
		missile->AddComponent<ecs::RigidbodyComponent>()->AddForce(force);
		//TODO: handle shooting sound
	}

private:
	ecs::TransformComponent* m_transform;
};

#endif // !__MISSILE_LAUNCHER_H__

