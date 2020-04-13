#ifndef __BULLET_H__
#define __BULLET_H__

#include <SDL.h>
#include "../lib/glm/glm.hpp"
#include "../engine/GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(string tag, Texture* sprite, glm::vec2 position, glm::vec2 direction);
	~Bullet();
	void virtual Update(float secs);

	
};

#endif
