//#include "SteeringBehavior.h"
//
//SteeringBehavior::SteeringBehavior(GameObject* agent)
//{
//	m_agent = agent;
//}
//
//glm::vec2 SteeringBehavior::Seek(glm::vec2 targetPos)
//{
//	glm::vec2 desiredVel = glm::normalize(targetPos - m_agent->GetPosition()) * m_agent->GetMaxVelocity();
//	return (desiredVel - m_agent->GetMomentum());
//}
//
//glm::vec2 SteeringBehavior::Pursuit()
//{
//	glm::vec2 toEvader = m_target->GetPosition() - m_agent->GetPosition();
//	double relativeDir = glm::dot(m_agent->GetDirection(), m_target->GetDirection());
//	if (glm::dot(toEvader, m_agent->GetDirection()) > 0 && relativeDir < -0.95) //acos(0.95) = 18 degrees
//	{
//		return Seek(m_target->GetPosition());
//	}
//
//	float lookAheadTime = glm::length(toEvader) / (m_agent->GetMaxVelocity() + glm::length(m_target->GetMomentum()));
//	glm::vec2 seek = m_target->GetPosition() + m_target->GetMomentum() * lookAheadTime;
//
//	return Seek(seek);
//}
//
//glm::vec2 SteeringBehavior::Flee()
//{
//	glm::vec2 desired = glm::normalize(m_agent->GetPosition() - m_target->GetPosition());
//	desired *= m_agent->GetMaxVelocity();
//	return (desired - m_agent->GetMomentum());
//}