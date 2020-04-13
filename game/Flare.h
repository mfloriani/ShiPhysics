#ifndef __FLARE_H__
#define __FLARE_H__

#include "../engine/GameObject.h"

class Flare : public GameObject
{
public:
	Flare(std::string tag, glm::vec2 position, SDL_Texture* sprite, glm::vec2 direction);
	~Flare();
	void virtual Update(float secs);
	
private:
	float m_duration;
	

};

#endif

