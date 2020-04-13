#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "SDL_mixer.h"
#include "../engine/GameObject.h"
#include "../engine/Animation.h"
#include "../engine/SteeringBehavior.h"

class Missile :	public GameObject
{
public:
	Missile(std::string tag, glm::vec2 position, SDL_Texture* sprite, GameObject* target, Mix_Chunk* explosion, Animation* explosionAnim);
	~Missile() {};
	
	void virtual Update(float secs);
	void virtual Draw(float secs);
	void SetFlare(GameObject* flare);
	bool IsFleeing();
	void Explode();

private:
	float m_fuel;
	GameObject* m_target;
	GameObject* m_flare;
	bool m_fleeing;
	Mix_Chunk* m_explosionAudio;
	Animation* m_explosionAnim;
	SteeringBehavior* m_steering;
};

#endif
