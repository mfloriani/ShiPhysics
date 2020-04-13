#ifndef __BULLET_H__
#define __BULLET_H__

#include <SDL.h>
#include "../lib/Vector2D.h"
#include "../engine/GameObject.h"

using namespace math;

class Bullet : public GameObject
{
public:
	Bullet(string tag, Texture* sprite, Vector2D position, Vector2D direction);
	~Bullet();
	void virtual Update(float secs);

	
};

#endif
