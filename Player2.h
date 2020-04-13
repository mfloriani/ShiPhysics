#ifndef __PLAYER2_H__
#define __PLAYER2_H__

#include "Ship.h"

class Player2 :	public Ship
{
public:
	Player2(Texture* sprite, Texture* bulletSprite, Mix_Chunk* bulletAudio, Mix_Chunk* missileAudio, Mix_Chunk* explosionAudio, Texture* missileSprite, Texture* flareTexture, Animation* explosionAnim);
	~Player2();

	void Input(SDL_Event* evt, vector<GameObject*> *gameObjects, GameObject* target);
};

#endif
