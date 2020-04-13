#include "Player1.h"


Player1::Player1(Texture* sprite, Texture* bulletSprite, Mix_Chunk* bulletAudio, Mix_Chunk* missileAudio, Mix_Chunk* explosionAudio, Texture* missileSprite, Texture* flareTexture, Animation* explosionAnim) :
Ship("player1", 1, sprite, bulletSprite, bulletAudio, missileAudio, explosionAudio, missileSprite, flareTexture, explosionAnim)
{
}


Player1::~Player1()
{
}

void Player1::Input(SDL_Event* evt, vector<GameObject*> *gameObjects, GameObject* target)
{
	if (!m_active) return;

	if (evt->type == SDL_KEYDOWN)
	{
		switch (evt->key.keysym.sym)
		{
		case SDLK_RIGHT:
			Ship::SetRotation(Ship::Rotation::RIGHT);
			break;
		case SDLK_LEFT:
			SetRotation(Ship::Rotation::LEFT);
			break;
		case SDLK_UP:
			SetTrustPressed(true);
			break;
		case SDLK_o:
			gameObjects->push_back(Shoot("bullet1"));
			break;
		case SDLK_l:
			if (m_missile == NULL || !m_missile->IsActive())
			{
				gameObjects->push_back(ShootMissile("missile1", target));
			}
			break;
		}
	}
	else if (evt->type == SDL_KEYUP)
	{
		switch (evt->key.keysym.sym)
		{
		case SDLK_RIGHT:
			SetRotation(Ship::Rotation::NONE);
			break;
		case SDLK_LEFT:
			SetRotation(Ship::Rotation::NONE);
			break;
		case SDLK_UP:
			SetTrustPressed(false);
			break;
		}
	}
}
