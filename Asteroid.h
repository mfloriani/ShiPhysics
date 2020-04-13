#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "GameObject.h"
#include "Animation.h"

class Asteroid : public GameObject
{
public:
	Asteroid(Vector2D position, float mass, Texture* sprite, Animation* explosionAnim);
	~Asteroid();
	void virtual Update(float secs);
	void virtual Draw(float secs);
	void Explode();

private:
	Animation* m_explosionAnim;
};

#endif
