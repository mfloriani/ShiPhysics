#ifndef __FLARE_H__
#define __FLARE_H__

#include "../engine/GameObject.h"

class Flare : public GameObject
{
public:
	Flare(string tag, Vector2D position, Texture* sprite, Vector2D direction);
	~Flare();
	void virtual Update(float secs);
	
private:
	float m_duration;
	

};

#endif

