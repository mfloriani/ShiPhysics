#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <vector>

namespace ecs
{
	class Observer;

	class Subject
	{
	public:
		virtual ~Subject() {}
		virtual void Notify() = 0;
		virtual void Register(Observer* observer);
		virtual void Unregister(Observer* observer);
	private:
		std::vector<Observer*> m_observer;
	};
}

#endif // !__SUBJECT_H__