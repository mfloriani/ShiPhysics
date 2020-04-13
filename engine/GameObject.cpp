#include "GameObject.h"
#include "../lib/glm/gtx/rotate_vector.hpp"
#include "../game/Arena.h"

GameObject::GameObject(string tag, glm::vec2 position, float mass, Texture* sprite) : m_position(position), m_direction(glm::vec2(1,0)), m_mass(mass), m_sprite(sprite), m_angleRadian(0.0f), m_angleDegree(0.0f), m_tag(tag), m_active(true), 
m_currentState(GameObject::States::alive)
{
	UpdateDirection();
	SetCollider();
}

GameObject::GameObject(string tag, glm::vec2 position, float mass, Texture* sprite, glm::vec2 direction) : m_position(position), m_mass(mass), m_sprite(sprite), m_angleRadian(0.0f), m_angleDegree(0.0f), m_direction(direction), m_tag(tag), m_active(true)
{
	SetCollider();
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
	m_direction = glm::normalize( glm::rotate(glm::vec2(1,0), m_angleRadian) );
	//SDL_Log("Dir %f %f", m_direction.x, m_direction.y);
}

glm::vec2 GameObject::CalculateForces()
{
	return glm::vec2();
}

void GameObject::Update(float secs)
{
	if (!m_active) return;

	glm::vec2 forces = CalculateForces();
	glm::vec2 accelSecs = (forces / m_mass) * secs;
	m_position += (m_momentum + (accelSecs * 0.5f)) * secs;
	m_momentum += accelSecs;

	SetCollider();
}

void GameObject::Draw(float secs)
{
	//cout << m_tag <<" " << m_position << endl;
	if (!m_active) return;
	/*if (m_tag == "player1")
	{
		SDL_Log("rad %f deg %f", m_angleRadian, m_angleDegree);
		
		glm::vec2 dirOffset = m_position + (m_direction * 50.f);
		SDL_SetRenderDrawColor(Arena::m_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(Arena::m_renderer, m_position.x, m_position.y, dirOffset.x, dirOffset.y);
	}*/
	m_sprite->Render(m_position.x, m_position.y, NULL, m_angleDegree, NULL, SDL_FLIP_NONE);
}

SDL_Rect GameObject::GetCollider()
{
	return m_collider;
}

glm::vec2 GameObject::GetPosition()
{
	return m_position;
}

glm::vec2 GameObject::GetDirection()
{
	return m_direction;
}

glm::vec2 GameObject::GetMomentum()
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
