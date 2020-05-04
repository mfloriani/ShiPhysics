#ifndef __STEERING_COMPONENT_H__
#define __STEERING_COMPONENT_H__

#include <bitset>
#include "../lib/glm/glm.hpp"
#include "Component.h"

namespace ecs
{
	typedef std::bitset<32> Behaviors;

	class GameObject;
	class TransformComponent;
	class RigidbodyComponent;

	enum BehaviorsType
	{
		None    = 0,
		Seek	= 1,
		Pursuit = 2,
		Flee	= 4
	};

	class SteeringComponent : public Component
	{
	public:
		SteeringComponent() :
			m_agent(nullptr),
			m_target(nullptr),
			m_agentTransform(nullptr),
			m_agentRigidbody(nullptr),
			m_targetTransform(nullptr),
			m_targetRigidbody(nullptr),
			m_currentBehaviors(0)
		{}

		~SteeringComponent() {}

		glm::vec2 Seek(glm::vec2 targetPos);
		glm::vec2 Pursuit();
		glm::vec2 Flee();

		void		SetTarget(GameObject* target);
		Behaviors	Enable(Behaviors behaviors);
		Behaviors	Disable(Behaviors behaviors);
		bool		IsEnabled(Behaviors behaviors);

		virtual void Init() override;
		virtual void Update(float dt) override;
		virtual void Render() override {}

	private:
		GameObject*			m_agent;
		GameObject*			m_target;
		TransformComponent* m_agentTransform;
		RigidbodyComponent* m_agentRigidbody;
		TransformComponent* m_targetTransform;
		RigidbodyComponent* m_targetRigidbody;
		Behaviors			m_currentBehaviors;

	};
}

#endif // !__STEERING_COMPONENT_H__

