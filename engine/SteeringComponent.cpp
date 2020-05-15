#include "SteeringComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "Engine.h"
#include "GameObjectManager.h"

namespace ecs
{
	glm::vec2 SteeringComponent::Seek(glm::vec2 targetPos)
	{
		glm::vec2 desiredVel = glm::normalize(targetPos - m_agentTransform->m_position) * m_agentRigidbody->GetMaxVelocity();
		return (desiredVel - m_agentRigidbody->GetMomentum());
	}

	glm::vec2 SteeringComponent::Pursuit()
	{
		glm::vec2 toEvader = m_targetTransform->m_position - m_agentTransform->m_position;
		double relativeDir = glm::dot(m_agentTransform->m_direction, m_targetTransform->m_direction);
		if (glm::dot(toEvader, m_agentTransform->m_direction) > 0 && relativeDir < -0.95) //acos(0.95) = 18 degrees
		{
			return Seek(m_targetTransform->m_position);
		}

		float lookAheadTime = glm::length(toEvader) / (m_agentRigidbody->GetMaxVelocity() + glm::length(m_targetRigidbody->GetMomentum()));
		glm::vec2 seek = m_targetTransform->m_position + m_targetRigidbody->GetMomentum() * lookAheadTime;

		return Seek(seek);
	}

	glm::vec2 SteeringComponent::Flee()
	{
		glm::vec2 desired = glm::normalize(m_agentTransform->m_position - m_targetTransform->m_position);
		desired *= m_agentRigidbody->GetMaxVelocity();
		return (desired - m_agentRigidbody->GetMomentum());
	}

	void SteeringComponent::SetTarget(uint32_t id)
	{
		m_target = id;
		m_targetTransform = Engine::GameObjectMgr->Get(m_target)->GetComponent<TransformComponent>();
		m_targetRigidbody = Engine::GameObjectMgr->Get(m_target)->GetComponent<RigidbodyComponent>();
	}

	void SteeringComponent::Init()
	{
		m_agent = m_owner;
		m_agentTransform = Engine::GameObjectMgr->Get(m_agent)->GetComponent<TransformComponent>();
		m_agentRigidbody = Engine::GameObjectMgr->Get(m_agent)->GetComponent<RigidbodyComponent>();
	}
	
	void SteeringComponent::Update(float dt)
	{
		if (IsEnabled(BehaviorsType::Seek)) m_agentRigidbody->AddForce(Seek(m_targetTransform->m_position));
		if (IsEnabled(BehaviorsType::Pursuit)) m_agentRigidbody->AddForce( Pursuit());
		if (IsEnabled(BehaviorsType::Flee)) m_agentRigidbody->AddForce(Flee());
	}
	
	Behaviors SteeringComponent::Enable(Behaviors behaviors)
	{
		m_currentBehaviors |= behaviors;
		return m_currentBehaviors;
	}

	Behaviors SteeringComponent::Disable(Behaviors behaviors)
	{
		m_currentBehaviors ^= behaviors;
		return m_currentBehaviors;
	}

	bool SteeringComponent::IsEnabled(Behaviors behaviors)
	{
		return (m_currentBehaviors & behaviors) != 0;
	}
}