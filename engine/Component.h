#ifndef __COMPONENT_H__
#define __COMPONENT_H__

namespace ecs
{
	class GameObject;

	class Component
	{
	public:
		GameObject* m_owner;

		virtual ~Component() {}
		virtual void Init() = 0;
		virtual void Update(float dt) = 0;
		virtual void Render() = 0;
	};
}

#endif // !__COMPONENT_H__