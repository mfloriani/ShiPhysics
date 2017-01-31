#ifndef __MISSILE_H__
#define __MISSILE_H__

#include "SDL_mixer.h"
#include "GameObject.h"
#include "Animation.h"

class Missile :	public GameObject
{
public:
	Missile(string tag, Vector2D position, Texture* sprite, GameObject* target, Mix_Chunk* explosion, Animation* explosionAnim);
	~Missile();
	Vector2D Seek(Vector2D targetPos);
	Vector2D Pursuit();
	Vector2D Flee();
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
};

#endif
