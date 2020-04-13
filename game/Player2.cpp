#include "Player2.h"


Player2::Player2(Texture* sprite, Texture* bulletSprite, Mix_Chunk* bulletAudio, Mix_Chunk* missileAudio, Mix_Chunk* explosionAudio, Texture* missileSprite, Texture* flareTexture, Animation* explosionAnim) :
Ship("player2", 1, sprite, bulletSprite, bulletAudio, missileAudio, explosionAudio, missileSprite, flareTexture, explosionAnim)
{
}


Player2::~Player2()
{
}

void Player2::Input(SDL_Event* evt, vector<GameObject*> *gameObjects, GameObject* target)
{
	if (!m_active) return;

	if (evt->type == SDL_KEYDOWN)
	{
		switch (evt->key.keysym.sym)
		{
		case SDLK_d:
			Ship::SetRotation(Ship::Rotation::RIGHT);
			break;
		case SDLK_a:
			SetRotation(Ship::Rotation::LEFT);
			break;
		case SDLK_w:
			SetTrustPressed(true);
			break;
		case SDLK_LCTRL:
			gameObjects->push_back(Shoot("bullet2"));
			break;
		case SDLK_LSHIFT:
			if (m_flare == NULL || !m_flare->IsActive())
			{
				gameObjects->push_back(ReleaseFlare("flare2", m_direction));
			}
			break;
		}
	}
	else if (evt->type == SDL_KEYUP)
	{
		switch (evt->key.keysym.sym)
		{
		case SDLK_d:
			SetRotation(Ship::Rotation::NONE);
			break;
		case SDLK_a:
			SetRotation(Ship::Rotation::NONE);
			break;
		case SDLK_w:
			SetTrustPressed(false);
			break;
		}
	}
}
