#ifndef __PLAYER2_H__
#define __PLAYER2_H__

#include "Ship.h"

class Player2 :	public Ship
{
public:
	Player2(
		SDL_Texture* sprite, 
		SDL_Texture* bulletSprite, 
		Mix_Chunk* bulletAudio, 
		Mix_Chunk* missileAudio, 
		Mix_Chunk* explosionAudio, 
		SDL_Texture* missileSprite, 
		SDL_Texture* flareTexture, 
		Animation* explosionAnim);
	~Player2();

	void Input(SDL_Event* evt, std::vector<GameObject*> *gameObjects, GameObject* target);
};

#endif
