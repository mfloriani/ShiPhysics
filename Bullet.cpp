#include "Bullet.h"


Bullet::Bullet(string tag, Texture* sprite, Vector2D position, Vector2D direction) : GameObject(tag, position, 1, sprite, direction)
{
}


Bullet::~Bullet()
{
}

void Bullet::Update(float secs)
{
	m_position += m_direction * 1000 * secs;
	SetCollider();
}
