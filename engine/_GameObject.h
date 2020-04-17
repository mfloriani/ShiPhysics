//#ifndef __GameObject_H__
//#define __GameObject_H__
//
//#include "../lib/glm/glm.hpp"
//#include <string>
//#include <SDL.h>
//
//class _GameObject
//{
//public:
//	_GameObject(std::string tag, glm::vec2 position, float mass, SDL_Texture* sprite);
//	_GameObject(std::string tag, glm::vec2 position, float mass, SDL_Texture* sprite, glm::vec2 direction);
//	
//	virtual ~_GameObject();
//
//	void virtual Update(float secs);
//	void virtual Draw();
//	SDL_Rect GetCollider();
//	//glm::vec2 GetPosition();
//	//glm::vec2 GetDirection();
//	//glm::vec2 GetMomentum();
//	float GetMaxVelocity()const { return m_maxVelocity; };
//	std::string GetTag();
//	bool IsActive();
//	enum States{alive, dying, respawning, dead};
//	int GetCurrentState();
//
//protected:
//	//glm::vec2 m_position;
//	//glm::vec2 m_momentum;
//	//SDL_Texture* m_sprite;
//	SDL_Rect m_collider;
//	//glm::vec2 m_direction;
//	//float m_mass;
//	//float m_angleRadian;
//	//float m_angleDegree;
//	float m_maxVelocity;
//	std::string m_tag;
//	bool m_active;
//	int m_currentState;
//	
//	//glm::vec2 virtual CalculateSteering();
//	//glm::vec2 virtual CalculateForces();
//	void SetCollider();
//	void _GameObject::UpdateDirection();
//
//private:
//	
//	
//};
//
//#endif
