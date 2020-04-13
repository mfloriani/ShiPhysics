#include "Bullet.h"


Bullet::Bullet(string tag, Texture* sprite, glm::vec2 position, glm::vec2 direction) : GameObject(tag, position, 1, sprite, direction)
{
}


Bullet::~Bullet()
{
}

void Bullet::Update(float secs)
{
	m_position += m_direction * 1000.0f * secs;
	SetCollider();
}
