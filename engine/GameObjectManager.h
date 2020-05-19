#ifndef __GAMEOBJECT_MANAGER_H__
#define __GAMEOBJECT_MANAGER_H__

#include <vector>
#include <map>

namespace ecs
{
	class GameObject;
	class PhysicsSystem;

	typedef std::vector<GameObject*>		GameObjectVector;
	typedef std::vector<uint32_t>			GameObjectIdVector;
	typedef std::map<uint32_t, GameObject*> GameObjectIdMap;

	class GameObjectManager
	{
	public:
		~GameObjectManager();

		GameObject* Instantiate();
		void AddToPipeline();
		void Free();
		void Destroy(uint32_t id);
		void RemoveFromPipeline();
		GameObject* Get(uint32_t id);
		
		friend class Engine;
		friend class PhysicsSystem;

	private:
		GameObjectVector	m_gameObjects;
		GameObjectIdVector	m_newGameObjects;
		GameObjectIdVector	m_destroyedGameObjects;
		GameObjectIdMap		m_gameObjectMappingId;

		uint32_t NextId()
		{
			static uint32_t id = 0;
			return ++id;
		}
	};
}

#endif // !__GAMEOBJECT_MANAGER_H__