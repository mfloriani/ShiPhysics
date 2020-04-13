#ifndef __ARENA_H__
#define __ARENA_H__


#include <vector>
#include <string>
#include "../engine/Texture.h"
#include "../engine/GameObject.h"
#include "../engine/Animation.h"
#include "Asteroid.h"
#include "Ship.h"

class Arena
{
public:
	Arena(Ship* player1, Ship* player2, Texture* asteroidTex, SDL_Rect* camera, Mix_Chunk* explosion, TTF_Font* font, SDL_Renderer* renderer, Animation* explosionAnim);
	~Arena();

	void Input(SDL_Event* evt);
	void Update(float secs);
	void Draw(float secs);
	void DrawHUD();
	void UpdateHUD();

	Texture* m_asteroidTexture;
	TTF_Font* m_font;
	static SDL_Renderer* m_renderer;
	Texture m_p1Armor;
	Texture m_p1Lifes;
	Texture m_p2Armor;
	Texture m_p2Lifes;
	Texture m_gameoverText;
	

private:
	vector<GameObject*> m_gameObjects;
	vector<GameObject*>::iterator obj;
	vector<GameObject*>::iterator obj2;
	SDL_Rect* m_camera;
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
	void GameOver(string message);
	GameObject* HasFlare();

};

#endif
