#include "Missile.h"


Missile::Missile(string tag, Vector2D position, Texture* sprite, GameObject* target, Mix_Chunk* explosion, Animation* explosionAnim) :
GameObject(tag, position, 1, sprite), m_target(target), m_fuel(3), m_flare(NULL), m_fleeing(false), m_explosionAudio(explosion), m_explosionAnim(explosionAnim)
{
	m_maxVelocity = 5;
}


Missile::~Missile()
{
}

Vector2D Missile::Seek(Vector2D targetPos)
{
	Vector2D desiredVel;
	desiredVel = targetPos - m_position;
	desiredVel.normalize();
	desiredVel *= m_maxVelocity;
	return (desiredVel - m_momentum);
}

Vector2D Missile::Pursuit()
{
	Vector2D toEvader = m_target->GetPosition() - m_position;
	double relativeDir = m_direction.dot(m_target->GetDirection());
	if (toEvader.dot(m_direction) > 0 && relativeDir < -0.95) //acos(0.95) = 18 degrees
		return Seek(m_target->GetPosition());
	
	double lookAheadTime = toEvader.size() / (m_maxVelocity + m_target->GetMomentum().size());
	Vector2D seek = m_target->GetPosition() + m_target->GetMomentum() * lookAheadTime;

	return Seek(seek);
}

Vector2D Missile::Flee()
{
	if (m_flare == NULL)
	{
		m_fleeing = false;
		return Vector2D();
	}

	Vector2D desired = m_position - m_flare->GetPosition();
	desired.normalize();
	desired *= m_maxVelocity;
	return (desired - m_momentum);
}

void Missile::Update(float secs)
{
	//Vector2D vel = Seek(m_target->GetPosition());
	Vector2D vel;
	if (m_flare != NULL && !m_fleeing)
	{
		float dist = ((m_position - m_flare->GetPosition()).size());
		//printf("dist=%f \n", dist);
		if (dist < 100)
			m_fleeing = true;
	}

	if (m_fleeing)
		vel = Flee();
	else
		vel = Pursuit();

	m_momentum += vel;
	m_position += m_momentum;
	m_direction = m_momentum.normalize();
	SetCollider();
	
	m_fuel -= secs;
	if (m_fuel <= 0)
		Explode();
}

void Missile::SetFlare(GameObject* flare)
{
	m_flare = flare;
}

bool Missile::IsFleeing()
{
	return m_fleeing;
}

void Missile::Explode()
{
	m_currentState = GameObject::States::dying;
	Mix_PlayChannel(-1, m_explosionAudio, 0);
	m_active = false;
	m_flare = NULL;
}

void Missile::Draw(float secs)
{
	if (m_currentState == GameObject::States::alive)
		GameObject::Draw(secs);
	else if (m_currentState == GameObject::States::dying)
	{
		bool ended = m_explosionAnim->Draw(secs, m_position.x, m_position.y);
		if (ended)
			m_currentState = GameObject::States::dead;
	}
}
