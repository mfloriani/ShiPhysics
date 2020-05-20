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
		GameObject(uint32_t id) : m_id(id) {}
		~GameObject();

		template<typename T, typename... TArgs>
		T* AddComponent(TArgs&&... args)
		{
			T* component(new T(std::forward<TArgs>(args)...));
			component->m_owner = m_id;

			//TODO: move component init to another place to avoid inter-dependencies
			//      might be a good idea to call it when all components are already added
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

		inline uint32_t Id() const { return m_id; }
		inline uint32_t Parent() { return m_parent; }
		inline void Parent(uint32_t id) { m_parent = id; }

	private:
		std::vector<Component*>						m_components;
		std::map<const std::type_info*, Component*>	m_componentType;
		uint32_t									m_id;
		uint32_t									m_parent;
	};
}

#endif // !__GAMEOBJECT_H__