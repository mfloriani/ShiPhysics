#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Vector2D.h"
#include "Texture.h"
#include <string>
#include "Config.h"

using namespace math;
using namespace std;

class GameObject
{
public:
	GameObject(string tag, Vector2D position, float mass, Texture* sprite);
	GameObject(string tag, Vector2D position, float mass, Texture* sprite, Vector2D direction);
	GameObject(string tag, Vector2D position, float mass, Texture* sprite, float angleDegree);
	virtual ~GameObject();

	void virtual Update(float secs);
	void virtual Draw(float secs);
	SDL_Rect GetCollider();
	Vector2D GetPosition();
	Vector2D GetDirection();
	Vector2D GetMomentum();
	float GetMaxVelocity()const { return m_maxVelocity; };
	string GetTag();
	bool IsActive();
	enum States{alive, dying, respawning, dead};
	int GetCurrentState();

protected:
	Vector2D m_position;
	Vector2D m_momentum;
	Texture* m_sprite;
	SDL_Rect m_collider;
	Vector2D m_direction;
	float m_mass;
	float m_angleRadian;
	float m_angleDegree;
	float m_maxVelocity;
	string m_tag;
	bool m_active;
	int m_currentState;
	
	//Vector2D virtual CalculateSteering();
	Vector2D virtual CalculateForces();
	void SetCollider();
	void GameObject::UpdateDirection();

private:
	
	
};

#endif
