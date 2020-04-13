#ifndef __BULLET_H__
#define __BULLET_H__
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"
#include "GameObject.h"

using namespace math;

class Bullet : public GameObject
{
public:
	Bullet(string tag, Texture* sprite, Vector2D position, Vector2D direction);
	~Bullet();
	void virtual Update(float secs);

	
};

#endif
