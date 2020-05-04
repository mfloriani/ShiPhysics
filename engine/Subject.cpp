#include "Subject.h"
#include "Observer.h"

namespace ecs
{
	void Subject::Register(Observer* observer)
	{
		auto it = std::find(m_observers.begin(), m_observers.end(), observer);
		if (it != m_observers.end()) return;

		m_observers.push_back(observer);
	}

	void Subject::Unregister(Observer* observer)
	{
		auto it = std::find(m_observers.begin(), m_observers.end(), observer);
		if (it == m_observers.end()) return;

		std::swap(*it, *(--m_observers.end()));
		m_observers.pop_back();
	}

	void Subject::Notify(Event* event)
	{
		for (auto o : m_observers)
		{
			o->OnNotify(event);
		}
	}
}