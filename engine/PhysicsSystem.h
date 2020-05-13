#ifndef __PHYSICS_SYSTEM_H__
#define __PHYSICS_SYSTEM_H__

#include <vector>
#include "Subject.h"

namespace ecs
{
	class GameObjectManager;
	class CollisionEvent;

	//TODO: turn it a singleton
	//		create System interface class
	class PhysicsSystem
	{
	public:
		PhysicsSystem(GameObjectManager* goMgr) : 
			m_gameObjectMgr(goMgr)
		{}

		~PhysicsSystem()
		{
			FreePreviousCollisionEvents();
		}

		void Update(float dt);

		Subject& OnCollisionEvent();
		
	private:
		Subject							m_onCollisionEvent;
		GameObjectManager*				m_gameObjectMgr;

		//TODO: create an event system to handle the pending events, instead of inside physicsSystem
		std::vector<CollisionEvent*>	m_collisionEvents;

		void FreePreviousCollisionEvents();
	};
}

#endif // !__PHYSICS_SYSTEM_H__