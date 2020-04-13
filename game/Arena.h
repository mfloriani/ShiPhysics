#ifndef __ARENA_H__
#define __ARENA_H__


#include <vector>
#include <string>
#include "../engine/GameObject.h"
#include "../engine/Animation.h"
#include "Asteroid.h"
#include "Ship.h"
#include <SDL_ttf.h>
#include "../engine/TextComponent.h"


class Arena
{
public:
	Arena(
		Ship* player1, 
		Ship* player2, 
		SDL_Texture* asteroidTex, 
		Mix_Chunk* explosion, 
		Animation* explosionAnim);
	~Arena();

	void Input(SDL_Event* evt);
	void Update(float secs);
	void Draw(float secs);
	void DrawHUD();
	void UpdateHUD();

	SDL_Texture* m_asteroidSDL_Texture;
	
	ecs::TextComponent m_p1Armor;
	ecs::TextComponent m_p1Lives;
	ecs::TextComponent m_p2Armor;
	ecs::TextComponent m_p2Lives;
	ecs::TextComponent m_gameoverText;
	

private:
	std::vector<GameObject*> m_gameObjects;
	std::vector<GameObject*>::iterator obj;
	std::vector<GameObject*>::iterator obj2;
	Ship* m_player1;
	Ship* m_player2;
	Mix_Chunk* m_explosionAudio;
	glm::vec2 m_p1InitialPosition;
	glm::vec2 m_p2InitialPosition;
	bool m_gameover;
	Animation* m_explosionAnim;

	GameObject* CreateAsteroid();
	bool HasAsteroidCollision(GameObject* obj);
	void SpawnPlayer1();
	void SpawnPlayer2();
	void GameOver(std::string message);
	GameObject* HasFlare();

};

#endif
