#ifndef __SHIP_H__
#define __SHIP_H__

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "../lib/glm/glm.hpp"
#include "../engine/GameObject.h"
#include "../engine/Animation.h"
#include "Bullet.h"
#include "Missile.h"
#include "Flare.h"

class Ship : public GameObject
{

public:
	enum Rotation{NONE, LEFT, RIGHT};
	
	Ship(
		std::string tag, 
		float mass, 
		SDL_Texture* sprite, 
		SDL_Texture* bulletSprite, 
		Mix_Chunk* bulletAudio, 
		Mix_Chunk* missileAudio, 
		Mix_Chunk* explosionAudio, 
		SDL_Texture* missileSprite, 
		SDL_Texture* flareSprite, 
		Animation* explosionAnim);
	~Ship();

	void virtual Input(SDL_Event* evt, std::vector<GameObject*> *gameObjects, GameObject* target);
	void virtual Update(float secs);
	void virtual Draw(float secs);
	void SetDamageByBullet(int damage);
	void SetDamageByMissile(int damage);
	void Explode();
	bool HasArmor();
	bool HasLives();
	int GetArmor();
	int GetLives();
	void Respawn(glm::vec2 position);
	void ArmNewMissile();
	void ArmNewFlare();
	void MissileExploded(glm::vec2 explosionSite);

protected:
	void SetRotation(Rotation rotation);
	void SetTrustPressed(bool pressed);
	glm::vec2 virtual CalculateForces();
	Bullet* Shoot(std::string tag);
	Missile* ShootMissile(std::string tag, GameObject* target);
	Flare* ReleaseFlare(std::string tag, glm::vec2 direction);
	
	Rotation m_rotation;
	bool m_trustPressed;
	int m_lives;
	int m_armor;
	SDL_Texture* m_bulletSprite;
	SDL_Texture* m_missileSprite;
	Mix_Chunk* m_bulletAudio;
	Mix_Chunk* m_MissileAudio;
	Mix_Chunk* m_explosionAudio;
	Missile* m_missile;
	glm::vec2 m_cannonPos;
	Flare* m_flare;
	SDL_Texture* m_flareSprite;
	Animation* m_explosionAnim;
	float m_respawnTime;

};

#endif
