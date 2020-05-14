#ifndef __PHYSICS_SYSTEM_H__
#define __PHYSICS_SYSTEM_H__

#include <vector>

namespace ecs
{
	class GameObjectManager;

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
			
		}

		void Update(float dt);
		
	private:
		GameObjectManager*	m_gameObjectMgr;
	};
}

#endif // !__PHYSICS_SYSTEM_H__