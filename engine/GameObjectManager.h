#ifndef __GAMEOBJECT_MANAGER_H__
#define __GAMEOBJECT_MANAGER_H__

#include <vector>
#include "GameObject.h"

namespace ecs
{
	typedef std::vector<GameObject*> GameObjectVector;

	class GameObjectManager
	{
	public:
		~GameObjectManager()
		{
			Free();
		}
		GameObject* AddGameObject()
		{
			GameObject* go = new GameObject;
			m_newGameObjects.emplace_back(go);
			return go;
		}

		void Update(float dt)
		{
			for (auto go : m_gameObjects)
			{
				go->Update(dt);
			}
			for (auto go : m_newGameObjects)
			{
				m_gameObjects.emplace_back(go);
			}
			m_newGameObjects.clear();
		}

		void Render()
		{
			for (auto go : m_gameObjects)
			{
				go->Render();
			}
		}

		void Free()
		{
			for (auto go : m_gameObjects)
			{
				delete go;
			}
			m_gameObjects.clear();
		}
				
	private:
		GameObjectVector m_gameObjects;
		GameObjectVector m_newGameObjects;
	};
}

#endif // !__GAMEOBJECT_MANAGER_H__