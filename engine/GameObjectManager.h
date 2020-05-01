#ifndef __GAMEOBJECT_MANAGER_H__
#define __GAMEOBJECT_MANAGER_H__

#include <vector>
#include "GameObject.h"
#include "BoxColliderComponent.h"
#include "CollisionSystem.h"

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

			CheckCollision();

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

		void CheckCollision()
		{
			//TODO: optimize the collision system
			//      keep colliders in a separated array
			//      probably move it to another part of the code, not inside this class
			for(int i = 0; i < m_gameObjects.size(); ++i)
			{
				if (m_gameObjects[i]->HasComponent<BoxColliderComponent>())
				{
					for (int j = i+1; j < m_gameObjects.size(); ++j)
					{
						if (m_gameObjects[j]->HasComponent<BoxColliderComponent>())
						{
							SDL_Rect boxL = m_gameObjects[i]->GetComponent<BoxColliderComponent>()->GetCollider();
							SDL_Rect boxR = m_gameObjects[j]->GetComponent<BoxColliderComponent>()->GetCollider();
							
							if (CheckBoxCollision(&boxL, &boxR))
							{
								//SDL_Log("Collision happened");
								//TODO: create event to inform the collision

							}
						}
					}
				}
			}
		}

	private:
		GameObjectVector m_gameObjects;
		GameObjectVector m_newGameObjects;
	};
}

#endif // !__GAMEOBJECT_MANAGER_H__