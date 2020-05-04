#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <vector>
#include <map>
#include <typeinfo>

namespace ecs
{
	class Component;

	class GameObject
	{
	public:
		GameObject() {}
		~GameObject();

		template<typename T, typename... TArgs>
		T* AddComponent(TArgs&&... args)
		{
			T* component(new T(std::forward<TArgs>(args)...));
			component->m_owner = this;
			component->Init();

			m_components.emplace_back(component);
			m_componentType[&typeid(*component)] = component;

			return component;
		}

		template<typename T>
		T* GetComponent()
		{
			return static_cast<T*>(m_componentType[&typeid(T)]);
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_componentType.count(&typeid(T));
		}

		void Update(float dt);
		void Render();
		void Free();

	private:
		std::vector<Component*>						m_components;
		std::map<const std::type_info*, Component*>	m_componentType;
	};
}

#endif // !__GAMEOBJECT_H__