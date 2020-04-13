#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "../lib/glm/glm.hpp"
#include "Texture.h"
#include <string>
#include "Config.h"

using namespace std;

class GameObject
{
public:
	GameObject(string tag, glm::vec2 position, float mass, Texture* sprite);
	GameObject(string tag, glm::vec2 position, float mass, Texture* sprite, glm::vec2 direction);
	GameObject(string tag, glm::vec2 position, float mass, Texture* sprite, float angleDegree);
	virtual ~GameObject();

	void virtual Update(float secs);
	void virtual Draw(float secs);
	SDL_Rect GetCollider();
	glm::vec2 GetPosition();
	glm::vec2 GetDirection();
	glm::vec2 GetMomentum();
	float GetMaxVelocity()const { return m_maxVelocity; };
	string GetTag();
	bool IsActive();
	enum States{alive, dying, respawning, dead};
	int GetCurrentState();

protected:
	glm::vec2 m_position;
	glm::vec2 m_momentum;
	Texture* m_sprite;
	SDL_Rect m_collider;
	glm::vec2 m_direction;
	float m_mass;
	float m_angleRadian;
	float m_angleDegree;
	float m_maxVelocity;
	string m_tag;
	bool m_active;
	int m_currentState;
	
	//glm::vec2 virtual CalculateSteering();
	glm::vec2 virtual CalculateForces();
	void SetCollider();
	void GameObject::UpdateDirection();

private:
	
	
};

#endif
