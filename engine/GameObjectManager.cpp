#include "GameObjectManager.h"
#include "GameObject.h"
#include "DestroyEvent.h"
#include "Engine.h"
#include "EventSystem.h"

namespace ecs
{
	GameObjectManager::~GameObjectManager()
	{
		Free();
	}

	GameObject* GameObjectManager::Instantiate()
	{
		uint32_t id = NextId();
		GameObject* go = new GameObject(id);
		m_gameObjectMappingId[id] = go;
		m_newGameObjects.emplace_back(id);
		return go;
	}

	void GameObjectManager::AddToPipeline()
	{
		for (auto id : m_newGameObjects)
		{
			auto go = Get(id);
			if (!go) continue;
			m_gameObjects.emplace_back(go);
		}
		m_newGameObjects.clear();
	}

	void GameObjectManager::Free()
	{
		for (auto [id, go] : m_gameObjectMappingId)
		{
			if (!go) continue;
			delete go;
			go = nullptr;
		}
		m_gameObjectMappingId.clear();
		m_newGameObjects.clear();
		m_destroyedGameObjects.clear();
		m_gameObjects.clear();
	}

	void GameObjectManager::Destroy(uint32_t id)
	{
		m_destroyedGameObjects.push_back(id);
		Engine::EventSys->Publish(new ecs::DestroyEvent(id));
		SDL_Log("Destroying %i", id);
	}

	void GameObjectManager::RemoveFromPipeline()
	{
		for (auto id : m_destroyedGameObjects)
		{
			auto goToDestroy = Get(id);
			if (!goToDestroy) continue;

			//swap the element to be destroyed with the last element and then remove it
			auto it = std::find(m_gameObjects.begin(), m_gameObjects.end(), goToDestroy);
			if (it == m_gameObjects.end()) continue;
			std::swap(*it, *(--m_gameObjects.end()));
			m_gameObjects.pop_back();

			delete goToDestroy;
			goToDestroy = nullptr;
			m_gameObjectMappingId[id] = nullptr;
		}
		m_destroyedGameObjects.clear();
	}

	GameObject* GameObjectManager::Get(uint32_t id)
	{
		auto it = m_gameObjectMappingId.find(id);
		if (it == m_gameObjectMappingId.end()) return nullptr;
		return it->second;
	}
}