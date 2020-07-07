#ifndef __OBSERVER_H__
#define __OBSERVER_H__

namespace ecs
{
	class Event;

	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void OnNotify(Event* event) = 0;
	};
}

#endif // !__OBSERVER_H__