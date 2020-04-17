//#include "Asteroid.h"
//
//
//Asteroid::Asteroid(
//	glm::vec2 position, 
//	float mass, 
//	SDL_Texture* sprite, 
//	Animation* explosionAnim) : 
//	GameObject(
//		"asteroid", 
//		position, 
//		mass, 
//		sprite), 
//	m_explosionAnim(explosionAnim)
//{
//	
//}
//
//Asteroid::~Asteroid()
//{
//
//}
//
//void Asteroid::Update(float secs)
//{
//	m_position += glm::vec2(-50,0) * secs;
//	SetCollider();
//	m_angleDegree += 180.0f * secs;
//}
//
//void Asteroid::Draw()
//{
//	if (m_currentState == GameObject::States::alive)
//		GameObject::Draw();
//	else if (m_currentState == GameObject::States::dying)
//	{
//		bool ended = m_explosionAnim->Draw(m_position.x, m_position.y);
//		if (ended)
//			m_currentState = GameObject::States::dead;
//	}
//}
//
//void Asteroid::Explode()
//{
//	m_currentState = States::dying;
//}
