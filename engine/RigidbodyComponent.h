#ifndef __RIGIDBODY_COMPONENT_H__
#define __RIGIDBODY_COMPONENT_H__

#include "../lib/glm/glm.hpp"
#include "Component.h"

namespace ecs
{
	class TransformComponent;

	class RigidbodyComponent : public Component
	{
	public:
		RigidbodyComponent() : 
			m_momentum(glm::vec2(0,0)), 
			m_force(glm::vec2(0, 0)),
			m_mass(1), 
			m_transform(nullptr),
			m_maxVelocity(0.1f)
		{}

		RigidbodyComponent(float mass, float maxVelocity) : 
			m_momentum(glm::vec2(0, 0)), 
			m_force(glm::vec2(0, 0)),
			m_mass(mass), 
			m_transform(nullptr),
			m_maxVelocity(maxVelocity)
		{}
		
		virtual void Init() override;

		virtual void Update(float dt) override;

		virtual void Render() override {}

		void AddForce(glm::vec2 force) { m_force += force; }
		inline float GetMaxVelocity() const { return m_maxVelocity; }
		inline glm::vec2 GetMomentum() const { return m_momentum; }

	private:
		glm::vec2			m_momentum;
		glm::vec2			m_force;
		float				m_mass;
		float				m_maxVelocity;
		TransformComponent* m_transform;

	};
}

#endif // !__RIGIDBODY_COMPONENT_H__