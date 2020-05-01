#ifndef __OBSERVER_H__
#define __OBSERVER_H__

namespace ecs
{
	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void update() = 0;
	};
}

#endif // !__OBSERVER_H__