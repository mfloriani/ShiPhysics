#ifndef __PLAYER1_H__
#define __PLAYER1_H__

#include "Ship.h"

class Player1 : public Ship
{
public:
	Player1(Texture* sprite, Texture* bulletSprite, Mix_Chunk* bulletAudio, Mix_Chunk* missileAudio, Mix_Chunk* explosionAudio, Texture* missileSprite, Texture* flareTexture, Animation* explosionAnim);
	~Player1();

	void Input(SDL_Event* evt, vector<GameObject*> *gameObjects, GameObject* target);
	
};

#endif
