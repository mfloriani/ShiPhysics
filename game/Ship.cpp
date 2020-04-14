#include "Ship.h"
#include "../lib/glm/gtx/rotate_vector.hpp"
#include "../engine/Constants.h"

Ship::Ship(
	std::string tag, 
	float mass, 
	SDL_Texture* sprite, 
	SDL_Texture* bulletSprite, 
	Mix_Chunk* bulletAudio, 
	Mix_Chunk* missileAudio, 
	Mix_Chunk* explosionAudio, 
	SDL_Texture* missileSprite, 
	SDL_Texture* flareSprite, 
	Animation* explosionAnim) :
	GameObject(tag, glm::vec2(0,0), mass, sprite),
	m_rotation(Rotation::NONE),
	m_trustPressed(false),
	m_lives(3),
	m_armor(100),
	m_bulletSprite(bulletSprite),
	m_bulletAudio(bulletAudio),
	m_MissileAudio(missileAudio),
	m_explosionAudio(explosionAudio),
	m_missileSprite(missileSprite),
	m_missile(NULL),
	m_cannonPos(glm::vec2(16,16)),
	m_flare(NULL),
	m_flareSprite(flareSprite),
	m_explosionAnim(explosionAnim)
{

}

Ship::~Ship()
{

}

void Ship::SetRotation(Rotation rotation)
{
	m_rotation = rotation;
}

void Ship::SetTrustPressed(bool pressed)
{
	m_trustPressed = pressed;
}

void Ship::Update(float secs)
{
	GameObject::Update(secs);

	if (m_position.x < 0)
		m_position.x = WINDOW_WIDTH;
	else if (m_position.x > WINDOW_WIDTH)
		m_position.x = 0;

	if (m_position.y < 0)
		m_position.y = WINDOW_HEIGHT;
	else if (m_position.y > WINDOW_HEIGHT)
		m_position.y = 0;

	SetCollider();

	if (m_rotation == Rotation::LEFT)
	{
		m_angleRadian -= glm::radians(180.0f) * secs;
		m_angleDegree = glm::degrees(m_angleRadian);
		UpdateDirection();
	}
	else if (m_rotation == Rotation::RIGHT)
	{
		m_angleRadian += glm::radians(180.0f) * secs;
		m_angleDegree = glm::degrees(m_angleRadian);
		UpdateDirection();
	}

	if (m_missile != NULL)
	{
		if (m_missile->GetCurrentState() == States::dying || m_missile->GetCurrentState() == States::dead)
		{
			MissileExploded(m_missile->GetPosition());
		}
	}
}

glm::vec2 Ship::CalculateForces()
{
	glm::vec2 forces(0,0);
	if (m_trustPressed)
	{
		glm::vec2 force = glm::rotate(glm::vec2(1,0) * 100.f, m_angleRadian);
		forces += force;
	}
	return forces;
}

void Ship::Draw(float secs)
{
	if (m_currentState == GameObject::States::alive)
	{
		GameObject::Draw(secs);
	}
	else if (m_currentState == GameObject::States::dying)
	{
		//printf("x=%f | y=%f \n", m_position.x, m_position.y);
		bool ended = m_explosionAnim->Draw(secs, static_cast<int>(m_position.x), static_cast<int>(m_position.y));
		if (ended)
		{
			m_respawnTime = 0;
			m_currentState = GameObject::States::respawning;
		}
	}
	else if (m_currentState == GameObject::States::respawning)
	{
		m_respawnTime += secs;
		if (m_respawnTime >= 1)//wait 1 second before respawning the player
			m_currentState = GameObject::States::alive;
	}
		
}


Bullet* Ship::Shoot(std::string tag)
{
	Mix_PlayChannel(-1, m_bulletAudio, 0);
	glm::vec2 pos = m_position + m_cannonPos;
	return new Bullet(tag, m_bulletSprite, pos, m_direction);
}

Missile* Ship::ShootMissile(std::string tag, GameObject* target)
{
	if (m_missile == NULL)
	{
		Mix_PlayChannel(-1, m_MissileAudio, 0);
		m_missile = new Missile(tag, m_position, m_missileSprite, target, m_explosionAudio, m_explosionAnim);
	}
	return m_missile;
}

Flare* Ship::ReleaseFlare(std::string tag, glm::vec2 direction)
{
	if (m_flare == NULL)
	{
		m_flare = new Flare(tag, m_position, m_flareSprite, m_momentum);
	}
	return m_flare;
}

void Ship::MissileExploded(glm::vec2 explosionSite)
{
	float dist = glm::length(m_position - explosionSite);
	//printf("dist=%f \n", dist);
	if (dist < 50)
	{
		SetDamageByMissile(50);
	}
	ArmNewMissile();
}

void Ship::ArmNewMissile()
{
	m_missile = NULL;
}

void Ship::ArmNewFlare()
{
	m_flare = NULL;
}

void Ship::SetDamageByBullet(int damage)
{
	Mix_PlayChannel(-1, m_explosionAudio, 0);
	m_armor -= damage;
	if (m_armor <= 0)
		Explode();
}

void Ship::SetDamageByMissile(int damage)
{
	Mix_PlayChannel(-1, m_explosionAudio, 0);
	m_armor -= damage;
	if (m_armor <= 0)
		Explode();
}

void Ship::Explode()
{
	m_currentState = GameObject::States::dying;
	Mix_PlayChannel(-1, m_explosionAudio, 0);
	m_armor = 0;
	m_lives--;
}

bool Ship::HasArmor()
{
	if (m_armor > 0)
		return true;
	return false;
}

bool Ship::HasLives()
{
	if (m_lives > 0) return true;

	m_active = false;
	return false;
}

void Ship::Input(SDL_Event* evt, std::vector<GameObject*> *gameObjects, GameObject* target)
{

}

int Ship::GetArmor()
{
	return m_armor;
}

int Ship::GetLives()
{
	return m_lives;
}

void Ship::Respawn(glm::vec2 position)
{
	m_armor = 100;
	m_position = position;
	m_momentum = glm::vec2();
	m_angleRadian = 0.0f;
	m_angleDegree = 0.0f;
	UpdateDirection();
}
