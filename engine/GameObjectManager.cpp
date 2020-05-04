#include "GameObjectManager.h"
#include "GameObject.h"

namespace ecs
{
	GameObjectManager::~GameObjectManager()
	{
		Free();
	}
	GameObject* GameObjectManager::NewGameObject()
	{
		GameObject* go = new GameObject;
		m_newGameObjects.emplace_back(go);
		return go;
	}

	void GameObjectManager::AddNewGameObjectsToPipeline()
	{
		for (auto go : m_newGameObjects)
		{
			m_gameObjects.emplace_back(go);
		}
		m_newGameObjects.clear();
	}

	void GameObjectManager::Free()
	{
		for (auto go : m_gameObjects)
		{
			delete go;
		}
		m_gameObjects.clear();
	}
}