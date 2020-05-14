#include "PhysicsSystem.h"
#include "GameObjectManager.h"
#include "BoxColliderComponent.h"
#include "CollisionSystem.h"
#include "CollisionEvent.h"
#include "GameObject.h"
#include "Engine.h"
#include "EventSystem.h"

namespace ecs
{
	void PhysicsSystem::Update(float dt)
	{
		for (unsigned int i = 0; i < m_gameObjectMgr->m_gameObjects.size(); ++i)
		{
			GameObject* goL = m_gameObjectMgr->m_gameObjects[i];

			if (goL->HasComponent<BoxColliderComponent>())
			{
				for (unsigned int j = i + 1; j < m_gameObjectMgr->m_gameObjects.size(); ++j)
				{
					GameObject* goR = m_gameObjectMgr->m_gameObjects[j];

					if (m_gameObjectMgr->m_gameObjects[j]->HasComponent<BoxColliderComponent>())
					{
						SDL_Rect boxL = goL->GetComponent<BoxColliderComponent>()->GetCollider();
						SDL_Rect boxR = goR->GetComponent<BoxColliderComponent>()->GetCollider();

						if (CheckBoxCollision(&boxL, &boxR))
						{
							//SDL_Log("Collision happened");

							//TODO: split collision in enter, on, exit
							
							CollisionEvent* event = new CollisionEvent{ goL , goR};
							
							//TODO: publish the event to EventSystem
							Engine::EventSys->Publish(event);
						}
					}
				}
			}
		}
	}
}