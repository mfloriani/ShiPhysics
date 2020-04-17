#ifndef __RIGIDBODY_COMPONENT_H__
#define __RIGIDBODY_COMPONENT_H__

#include "../lib/glm/glm.hpp"
#include "TransformComponent.h"

namespace ecs
{
	class RigidbodyComponent : public Component
	{
	public:
		RigidbodyComponent() : 
			m_momentum(glm::vec2(0,0)), 
			m_force(glm::vec2(0, 0)),
			m_mass(1), 
			m_transform(nullptr)
		{}

		RigidbodyComponent(float mass) : 
			m_momentum(glm::vec2(0, 0)), 
			m_force(glm::vec2(0, 0)),
			m_mass(mass), 
			m_transform(nullptr)
		{}
		
		virtual void Init() override 
		{
			m_transform = m_owner->GetComponent<TransformComponent>();
		}

		virtual void Update(float dt) override 
		{
			//TODO: clamp max velocity
			glm::vec2 acceleration = (m_force / m_mass) * dt;
			m_transform->m_position += (m_momentum + (acceleration * 0.5f)) * dt;
			m_momentum += acceleration;
			m_force = glm::vec2(0, 0);
		}

		virtual void Render() override {}

		void AddForce(glm::vec2 force) { m_force += force; }

	private:
		glm::vec2			m_momentum;
		glm::vec2			m_force;
		float				m_mass;
		TransformComponent* m_transform;
	};
}

#endif // !__RIGIDBODY_COMPONENT_H__