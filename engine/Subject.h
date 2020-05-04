#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>

namespace ecs
{
	class Observer;
	class Event;

	class Subject
	{
	public:
		virtual ~Subject() {}
		virtual void Notify(Event* event);
		virtual void Register(Observer* observer);
		virtual void Unregister(Observer* observer);
	protected:
		std::vector<Observer*> m_observers;
	};
}

#endif // !__SUBJECT_H__