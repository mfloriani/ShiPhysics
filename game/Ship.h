#ifndef __SHIP_H__
#define __SHIP_H__

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "../lib/Vector2D.h"
#include "../engine/GameObject.h"
#include "../engine/Animation.h"
#include "Bullet.h"
#include "Missile.h"
#include "Flare.h"

using namespace math;

class Ship : public GameObject
{

public:
	enum Rotation{NONE, LEFT, RIGHT};
	
	Ship(string tag, float mass, Texture* sprite, Texture* bulletSprite, Mix_Chunk* bulletAudio, Mix_Chunk* missileAudio, Mix_Chunk* explosionAudio, Texture* missileSprite, Texture* flareSprite, Animation* explosionAnim);
	~Ship();

	void virtual Input(SDL_Event* evt, vector<GameObject*> *gameObjects, GameObject* target);
	void virtual Update(float secs);
	void virtual Draw(float secs);
	void SetDamageByBullet(int damage);
	void SetDamageByMissile(int damage);
	void Explode();
	bool HasArmor();
	bool HasLives();
	int GetArmor();
	int GetLives();
	void Respawn(Vector2D position);
	void ArmNewMissile();
	void ArmNewFlare();
	void MissileExploded(Vector2D explosionSite);

protected:
	void SetRotation(Rotation rotation);
	void SetTrustPressed(bool pressed);
	Vector2D virtual CalculateForces();
	Bullet* Shoot(string tag);
	Missile* ShootMissile(string tag, GameObject* target);
	Flare* ReleaseFlare(string tag, Vector2D direction);
	
	Rotation m_rotation;
	bool m_trustPressed;
	int m_lives;
	int m_armor;
	Texture* m_bulletSprite;
	Texture* m_missileSprite;
	Mix_Chunk* m_bulletAudio;
	Mix_Chunk* m_MissileAudio;
	Mix_Chunk* m_explosionAudio;
	Missile* m_missile;
	Vector2D m_cannonPos;
	Flare* m_flare;
	Texture* m_flareSprite;
	Animation* m_explosionAnim;
	float m_respawnTime;

};

#endif
