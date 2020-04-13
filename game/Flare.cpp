#include "Flare.h"


Flare::Flare(string tag, glm::vec2 position, Texture* sprite, glm::vec2 direction) : GameObject(tag, position, 1, sprite, direction), m_duration(5)
{
	
}


Flare::~Flare()
{
}

void Flare::Update(float secs)
{
	m_momentum = m_direction * 2.0f * secs;
	m_position += m_momentum;
	SetCollider();

	m_duration -= secs;
	if (m_duration <= 0)
		m_active = false;
}
