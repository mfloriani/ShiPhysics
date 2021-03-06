#include "RigidbodyComponent.h"
#include <SDL.h>
#include "GameObject.h"
#include "TransformComponent.h"
#include "Engine.h"
#include "GameObjectManager.h"

namespace ecs
{
	void RigidbodyComponent::Init()
	{
		m_transform = Engine::GameObjectMgr->Get(m_owner)->GetComponent<TransformComponent>();
	}

	void RigidbodyComponent::Update(float dt)
	{
		glm::vec2 acceleration = (m_force / m_mass) * dt;
		m_transform->m_position += (m_momentum + (acceleration * 0.5f)) * dt;
		m_momentum += acceleration;
		m_momentum = glm::clamp(m_momentum, -m_maxVelocity, m_maxVelocity);
		m_force = glm::vec2(0, 0);
	}
}