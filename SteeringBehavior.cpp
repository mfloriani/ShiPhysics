#include "SteeringBehavior.h"

SteeringBehavior::SteeringBehavior(GameObject* agent)
{
	m_agent = agent;
}

math::Vector2D SteeringBehavior::Seek(math::Vector2D targetPos)
{
	math::Vector2D desiredVel = ((targetPos - m_agent->GetPosition()).normalize()) * m_agent->GetMaxVelocity();
	return (desiredVel - m_agent->GetMomentum());
}

math::Vector2D SteeringBehavior::Pursuit()
{
	math::Vector2D toEvader = m_target->GetPosition() - m_agent->GetPosition();
	double relativeDir = m_agent->GetDirection().dot(m_target->GetDirection());
	if (toEvader.dot(m_agent->GetDirection()) > 0 && relativeDir < -0.95) //acos(0.95) = 18 degrees
	{
		return Seek(m_target->GetPosition());
	}

	double lookAheadTime = toEvader.size() / (m_agent->GetMaxVelocity() + m_target->GetMomentum().size());
	math::Vector2D seek = m_target->GetPosition() + m_target->GetMomentum() * lookAheadTime;

	return Seek(seek);
}

math::Vector2D SteeringBehavior::Flee()
{
	math::Vector2D desired = m_agent->GetPosition() - m_target->GetPosition();
	desired.normalize();
	desired *= m_agent->GetMaxVelocity();
	return (desired - m_agent->GetMomentum());
}