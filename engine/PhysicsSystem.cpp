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
		//TODO: change the engine to keep track of the gameobjects with colliders instead of looping throgh entire vector
		for (unsigned int i = 0; i < m_gameObjectMgr->m_gameObjects.size(); ++i)
		{
			GameObject* goL = m_gameObjectMgr->m_gameObjects[i];

			if (goL->HasComponent<BoxColliderComponent>())
			{
				for (unsigned int j = i + 1; j < m_gameObjectMgr->m_gameObjects.size(); ++j)
				{
					GameObject* goR = m_gameObjectMgr->m_gameObjects[j];

					if (goL->Id() == goR->Parent() || goL->Parent() == goR->Id()) continue;

					if (m_gameObjectMgr->m_gameObjects[j]->HasComponent<BoxColliderComponent>())
					{
						SDL_Rect boxL = goL->GetComponent<BoxColliderComponent>()->GetCollider();
						SDL_Rect boxR = goR->GetComponent<BoxColliderComponent>()->GetCollider();

						if (CheckBoxCollision(&boxL, &boxR))
						{
							SDL_Log("collision between %i and %i", goL->Id(), goR->Id());

							//TODO: split collision in enter, on, exit
							
							//TODO: split in 2 events, one for each GO??
							CollisionEvent* event = new CollisionEvent{ goL->Id() , goR->Id()};							
							Engine::EventSys->Publish(event);
						}
					}
				}
			}
		}
	}
}