#ifndef __GAMEOBJECT_MANAGER_H__
#define __GAMEOBJECT_MANAGER_H__

#include <vector>

namespace ecs
{
	class GameObject;
	class PhysicsSystem;

	typedef std::vector<GameObject*> GameObjectVector;

	class GameObjectManager
	{
	public:
		~GameObjectManager();

		GameObject* Instantiate();
		void AddToPipeline();
		void Free();
		void Destroy(GameObject* gameobject);
		void RemoveFromPipeline();

		friend class Engine;
		friend class PhysicsSystem;

	private:
		GameObjectVector	m_gameObjects;
		GameObjectVector	m_newGameObjects;
		GameObjectVector	m_destroyedGameObjects;
	};
}

#endif // !__GAMEOBJECT_MANAGER_H__