#ifndef __PLAYER1_H__
#define __PLAYER1_H__

#include "Ship.h"

class Player1 : public Ship
{
public:
	Player1(
		SDL_Texture* sprite, 
		SDL_Texture* bulletSprite, 
		Mix_Chunk* bulletAudio, 
		Mix_Chunk* missileAudio, 
		Mix_Chunk* explosionAudio, 
		SDL_Texture* missileSprite, 
		SDL_Texture* flareTexture, 
		Animation* explosionAnim);
	~Player1();

	void Input(SDL_Event* evt, std::vector<GameObject*> *gameObjects, GameObject* target);
	
};

#endif
