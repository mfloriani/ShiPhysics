#include "Missile.h"


Missile::Missile(
	std::string tag, 
	glm::vec2 position, 
	SDL_Texture* sprite, 
	GameObject* target, 
	Mix_Chunk* explosion, 
	Animation* explosionAnim) :
	GameObject(tag, position, 1, sprite), 
	m_target(target), 
	m_fuel(3), 
	m_flare(NULL), 
	m_fleeing(false), 
	m_explosionAudio(explosion), 
	m_explosionAnim(explosionAnim)
{
	m_maxVelocity = 5;
	m_steering = new SteeringBehavior(this);
	m_steering->SetTarget(target);
}

void Missile::Update(float secs)
{
	glm::vec2 vel;
	if (m_flare != NULL && !m_fleeing)
	{
		float dist = glm::length(m_position - m_flare->GetPosition());
		//printf("dist=%f \n", dist);
		if (dist < 100) m_fleeing = true;
	}

	if (m_fleeing) 
	{
		if (m_flare == NULL)
		{
			m_fleeing = false;
			vel = glm::vec2();
		}
		else
		{
			vel = m_steering->Flee();
		}
	}
	else
	{
		vel = m_steering->Pursuit();
	}

	m_momentum += vel;
	m_position += m_momentum;
	m_direction = glm::normalize(m_momentum);
	SetCollider();
	
	m_fuel -= secs;
	if (m_fuel <= 0) Explode();
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
	{
		GameObject::Draw(secs);
	}
	else if (m_currentState == GameObject::States::dying)
	{
		bool ended = m_explosionAnim->Draw(secs, m_position.x, m_position.y);
		if (ended) m_currentState = GameObject::States::dead;
	}
}
