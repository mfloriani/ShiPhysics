#ifndef __SYSTEM_H__
#define __SYSTEM_H__

namespace ecs
{
	class System
	{
		virtual void Update(float dt) = 0;
	};
}

#endif // !__SYSTEM_H__