#include "GameObject.h"

GameObject::GameObject(string tag, Vector2D position, float mass, Texture* sprite) : m_position(position), m_mass(mass), m_sprite(sprite), m_angleRadian(0.0f), m_angleDegree(0.0f), m_tag(tag), m_active(true), 
m_currentState(GameObject::States::alive)
{
	UpdateDirection();
	SetCollider();
}

GameObject::GameObject(string tag, Vector2D position, float mass, Texture* sprite, Vector2D direction) : m_position(position), m_mass(mass), m_sprite(sprite), m_angleRadian(0.0f), m_angleDegree(0.0f), m_direction(direction), m_tag(tag), m_active(true)
{
	SetCollider();
}

GameObject::GameObject(string tag, Vector2D position, float mass, Texture* sprite, float angleDegree) : m_position(position), m_mass(mass), m_sprite(sprite), m_angleDegree(angleDegree), m_tag(tag), m_active(true)
{
	SetCollider();
	m_angleRadian = toRadians(angleDegree);
	UpdateDirection();
}


GameObject::~GameObject()
{
}

void GameObject::SetCollider()
{
	if (m_sprite != NULL)
	{
		SDL_Rect boxCollider;
		boxCollider.x = m_position.x;
		boxCollider.y = m_position.y;
		boxCollider.w = m_sprite->GetWidth();
		boxCollider.h = m_sprite->GetHeight();
		m_collider = boxCollider;
	}
}

void GameObject::UpdateDirection()
{
	m_direction = Vector2D::newBySizeAngle(1, m_angleRadian).normalize();
}

Vector2D GameObject::CalculateForces()
{
	return Vector2D();
}

void GameObject::Update(float secs)
{
	if (!m_active) return;

	Vector2D forces = CalculateForces();
	Vector2D accelSecs = (forces / m_mass) * secs;
	m_position += (m_momentum + (accelSecs / 2)) * secs;
	m_momentum += accelSecs;

	SetCollider();
}

void GameObject::Draw(float secs)
{
	//cout << m_tag <<" " << m_position << endl;
	if (!m_active) return;
	m_sprite->Render(m_position.x, m_position.y, NULL, m_angleDegree, NULL, SDL_FLIP_NONE);
}

SDL_Rect GameObject::GetCollider()
{
	return m_collider;
}

Vector2D GameObject::GetPosition()
{
	return m_position;
}

Vector2D GameObject::GetDirection()
{
	return m_direction;
}

Vector2D GameObject::GetMomentum()
{
	return m_momentum;
}

string GameObject::GetTag()
{
	return m_tag;
}

bool GameObject::IsActive()
{
	return m_active;
}

int GameObject::GetCurrentState()
{
	return m_currentState;
}
