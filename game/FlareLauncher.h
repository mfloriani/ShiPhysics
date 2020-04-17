#ifndef __FLARE_LAUNCHER_H__
#define __FLARE_LAUNCHER_H__

#include "../engine/Component.h"

class FlareLauncher : public ecs::Component
{
public:
	virtual ~FlareLauncher() {}
	virtual void Init() override
	{
		m_transform = m_owner->GetComponent<ecs::TransformComponent>();
	}
	virtual void Update(float dt) override {}
	virtual void Render() override {}

	void Launch()
	{
		ecs::GameObject* flare = ecs::Engine::GameObjectMgr->AddGameObject();
		flare->AddComponent<ecs::TransformComponent>(m_transform->m_position, m_transform->m_direction, 0.f);
		flare->AddComponent<ecs::SpriteComponent>("flare");
		flare->AddComponent<ecs::BoxColliderComponent>(0, 0, 10, 10);
		//glm::vec2 force = glm::rotate(glm::vec2(1, 0) * 20.f, m_transform->m_angle);
		//flare->AddComponent<ecs::RigidbodyComponent>()->AddForce(force);
		//TODO: handle sound
	}

private:
	ecs::TransformComponent* m_transform;
};

#endif // !__FLARE_LAUNCHER_H__

