#include "GameObjectManager.h"
#include "GameObject.h"

namespace ecs
{
	GameObjectManager::~GameObjectManager()
	{
		Free();
	}
	GameObject* GameObjectManager::Instantiate()
	{
		GameObject* go = new GameObject;
		m_newGameObjects.emplace_back(go);
		return go;
	}

	void GameObjectManager::AddToPipeline()
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
			if (!go) continue;
			delete go;
			go = nullptr;
		}
		m_gameObjects.clear();
	}

	void GameObjectManager::Destroy(GameObject* gameobject)
	{
		m_destroyedGameObjects.push_back(gameobject);
	}

	void GameObjectManager::RemoveFromPipeline()
	{
		for (auto toDestroy : m_destroyedGameObjects)
		{
			auto it = std::find(m_gameObjects.begin(), m_gameObjects.end(), toDestroy);
			if (it == m_gameObjects.end()) continue;
			
			std::swap(*it, *(--m_gameObjects.end()));
			m_gameObjects.pop_back();

			delete toDestroy;
			toDestroy = nullptr;
		}
		m_destroyedGameObjects.clear();
	}
}