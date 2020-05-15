#ifndef __COMPONENT_H__
#define __COMPONENT_H__

namespace ecs
{
	class Component
	{
	public:
		virtual ~Component() {}
		virtual void Init() = 0;
		virtual void Update(float dt) = 0;
		virtual void Render() = 0;
	
		unsigned int m_owner;
	};
}

#endif // !__COMPONENT_H__