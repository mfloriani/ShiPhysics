#include "Arena.h"
#include "../engine/Engine.h"
#include "../engine/Constants.h"

Arena::Arena(
	Ship* player1,
	Ship* player2,
	SDL_Texture* asteroidTex,
	Mix_Chunk* explosion,
	Animation* explosionAnim) :
	m_asteroidSDL_Texture(asteroidTex),
	m_player1(player1),
	m_player2(player2),
	m_explosionAudio(explosion),
	m_gameover(false),
	m_explosionAnim(explosionAnim),
	m_p1Armor({ UI_ARMOR_P1_X, UI_ARMOR_P1_Y }, "100", UI_FONT_FAMILY, { 255, 0, 0 }),
	m_p1Lives({ UI_LIFE_P1_X, UI_LIFE_P1_Y }, "3", UI_FONT_FAMILY, { 255, 0, 0 }),
	m_p2Armor({ UI_ARMOR_P2_X, UI_ARMOR_P2_Y }, "100", UI_FONT_FAMILY, { 0, 0, 255 }),
	m_p2Lives({ UI_LIFE_P2_X, UI_LIFE_P2_Y }, "3", UI_FONT_FAMILY, { 0, 0, 255 }),
	m_gameoverText({ UI_GAMEOVER_X, UI_GAMEOVER_Y }, "", UI_FONT_FAMILY, { 255, 255, 255 })
{

	m_p1InitialPosition = glm::vec2(WINDOW_WIDTH/2, 16);
	m_p2InitialPosition = glm::vec2(WINDOW_WIDTH/2, WINDOW_HEIGHT - 32);

	SpawnPlayer1();
	SpawnPlayer2();

	for (int i = 0; i < 1; i++)
		m_gameObjects.push_back(CreateAsteroid());
}


Arena::~Arena()
{

}

void Arena::Input(SDL_Event* evt)
{
	m_player1->Input(evt, &m_gameObjects, m_player2);
	m_player2->Input(evt, &m_gameObjects, m_player1);
}

bool Arena::HasAsteroidCollision(GameObject* obj)
{
	for (obj2 = m_gameObjects.begin(); obj2 != m_gameObjects.end(); ++obj2)
	{
		if ((*obj2) != NULL)
		{
			if ((*obj2)->GetTag() == "asteroid" && SDL_HasIntersection(&(*obj2)->GetCollider(), &obj->GetCollider()))
			{
				Mix_PlayChannel(-1, m_explosionAudio, 0);
				//(*obj2) = NULL;//acaba com o objeto
				//(*obj2) = CreateAsteroid();//criar novo aster�ide sempre que sair da tela
				Asteroid* asteroid = dynamic_cast<Asteroid*>(*obj2);
				asteroid->Explode();
				return true;
			}
		}
	}
	return false;
}

GameObject* Arena::HasFlare()
{
	for (obj2 = m_gameObjects.begin(); obj2 != m_gameObjects.end(); ++obj2)
	{
		if ((*obj2) != NULL)
		{
			if ((*obj2)->GetTag() == "flare2")
			{
				return (*obj2);
			}
		}
	}
	return NULL;
}

void Arena::Update(float secs)
{
	m_player1->Update(secs);
	m_player2->Update(secs);

	for (obj = m_gameObjects.begin(); obj != m_gameObjects.end(); ++obj)
	{
		if ((*obj) == NULL) continue;

		if ((*obj)->GetCurrentState() == GameObject::States::dying)
		{
			continue;
		}
		else if ((*obj)->GetCurrentState() == GameObject::States::dead)
		{
			if ((*obj)->GetTag() == "asteroid")
			{
				(*obj) = CreateAsteroid();
			}
			else
			{
				(*obj) = NULL;
			}
			continue;
		}

		if (!(*obj)->IsActive())
		{
			if ((*obj)->GetTag() == "flare2")
			{
				m_player2->ArmNewFlare();
			}
			else if ((*obj)->GetTag() == "missile1")
			{
				m_player1->MissileExploded((*obj)->GetPosition());
				m_player1->ArmNewMissile();
			}
			(*obj) = NULL;//acaba com o objeto
			continue;
		}

		(*obj)->Update(secs);

		if ((*obj)->GetTag() == "bullet1")
		{
			if (SDL_HasIntersection(&m_player2->GetCollider(), &(*obj)->GetCollider()))
			{
				m_player2->SetDamageByBullet(10);
				(*obj) = NULL;//acaba com o objeto
				continue;
			}

			if (HasAsteroidCollision((*obj)))
			{
				(*obj) = NULL;//acaba com o objeto
				continue;//pr�ximo obj da fila
			}
		}
		else if ((*obj)->GetTag() == "bullet2")
		{
			if (SDL_HasIntersection(&m_player1->GetCollider(), &(*obj)->GetCollider()))
			{
				m_player1->SetDamageByBullet(10);
				(*obj) = NULL;//acaba com o objeto
				continue;
			}

			if (HasAsteroidCollision((*obj)))
			{
				(*obj) = NULL;//acaba com o objeto
				continue;//pr�ximo obj da fila
			}
		}
		else if ((*obj)->GetTag() == "asteroid")
		{
			if (SDL_HasIntersection(&m_player1->GetCollider(), &(*obj)->GetCollider()))
			{
				Asteroid* asteroid = dynamic_cast<Asteroid*>(*obj);
				asteroid->Explode();
				//(*obj) = CreateAsteroid();//criar novo aster�ide sempre que sair da tela
				m_player1->Explode();
				continue;
			}

			if (SDL_HasIntersection(&m_player2->GetCollider(), &(*obj)->GetCollider()))
			{
				Asteroid* asteroid = dynamic_cast<Asteroid*>(*obj);
				asteroid->Explode();
				//(*obj) = CreateAsteroid();//criar novo aster�ide sempre que sair da tela
				m_player2->Explode();
				continue;
			}
		}
		else if ((*obj)->GetTag() == "missile1")
		{
			Missile* missile = dynamic_cast<Missile*>(*obj);
			if (SDL_HasIntersection(&m_player2->GetCollider(), &(*obj)->GetCollider()))
			{
				m_player2->SetDamageByMissile(50);
				missile->Explode();
				m_player1->MissileExploded((*obj)->GetPosition());
				m_player1->ArmNewMissile();
				//(*obj) = NULL;//acaba com o objeto
				continue;
			}

			if (HasAsteroidCollision((*obj)))
			{
				missile->Explode();
				m_player1->MissileExploded((*obj)->GetPosition());
				m_player1->ArmNewMissile();
				//(*obj) = NULL;//acaba com o objeto
				continue;//pr�ximo obj da fila
			}

			GameObject* flare = HasFlare();
			missile->SetFlare(flare);
		}

		if (!SDL_HasIntersection(&(*obj)->GetCollider(), ecs::Engine::Camera))//objeto continua na tela?
		{
			if ((*obj)->GetTag() == "asteroid")
				(*obj) = CreateAsteroid();//criar novo aster�ide sempre que sair da tela
			else if ((*obj)->GetTag() == "missile1")
			{
				(*obj) = NULL;//acaba com o objeto
				m_player1->ArmNewMissile();
			}
			else if ((*obj)->GetTag() == "flare2")
			{
				(*obj) = NULL;//acaba com o objeto
				m_player2->ArmNewFlare();
			}
			else
				(*obj) = NULL;//acaba com o objeto
		}
	}

	UpdateHUD();

	if (!m_player1->HasArmor() && m_player1->HasLives() && m_player1->GetCurrentState() == GameObject::States::alive)
		SpawnPlayer1();
	else if (!m_player1->HasLives())
		GameOver("Player 2 venceu!!! Aperte ENTER para recomecar.");


	if (!m_player2->HasArmor() && m_player2->HasLives() && m_player2->GetCurrentState() == GameObject::States::alive)
		SpawnPlayer2();
	else if (!m_player2->HasLives())
		GameOver("Player 1 venceu!!! Aperte ENTER para recomecar.");

}

void Arena::GameOver(std::string message)
{
	m_gameover = true;
	m_gameoverText.SetText(message);
}

void Arena::UpdateHUD()
{
	std::string armor;
	std::string lives;
	
	armor = "Player 1    Armor: " + std::to_string(m_player1->GetArmor());
	lives = "Lives: " + std::to_string(m_player1->GetLives());

	m_p1Armor.SetText(armor);
	m_p1Lives.SetText(lives);

	armor = "Player 2    Armor: " + std::to_string(m_player2->GetArmor());
	lives = "Lives: " + std::to_string(m_player2->GetLives());

	m_p2Armor.SetText(armor);
	m_p2Lives.SetText(lives);
}

void Arena::DrawHUD()
{
	m_p1Armor.Render();
	m_p1Lives.Render();

	m_p2Armor.Render();
	m_p2Lives.Render();
}

void Arena::Draw(float secs)
{
	m_player1->Draw(secs);
	m_player2->Draw(secs);

	for (obj = m_gameObjects.begin(); obj != m_gameObjects.end(); ++obj)
	{
		if ((*obj) != NULL) (*obj)->Draw(secs);
	}
	DrawHUD();

	if (m_gameover) m_gameoverText.Render();
}

GameObject* Arena::CreateAsteroid()
{
	int x = WINDOW_WIDTH;
	int y = rand() % WINDOW_HEIGHT;
	return new Asteroid(glm::vec2(x, y), 1, m_asteroidSDL_Texture, m_explosionAnim);
}

void Arena::SpawnPlayer1()
{
	m_player1->Respawn(m_p1InitialPosition);
}

void Arena::SpawnPlayer2()
{
	m_player2->Respawn(m_p2InitialPosition);
}
