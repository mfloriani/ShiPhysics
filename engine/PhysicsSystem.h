#ifndef __PHYSICS_SYSTEM_H__
#define __PHYSICS_SYSTEM_H__

#include <vector>
#include "System.h"

namespace ecs
{
	class GameObjectManager;

	//TODO: turn it a singleton
	//		create System interface class
	class PhysicsSystem : public System
	{
	public:
		PhysicsSystem(GameObjectManager* goMgr) : 
			m_gameObjectMgr(goMgr)
		{}

		~PhysicsSystem()
		{
			
		}

		virtual void Update(float dt) override;
		
	private:
		GameObjectManager*	m_gameObjectMgr;

		inline void PhysicsSystem::CheckCollisions();
	};
}

#endif // !__PHYSICS_SYSTEM_H__