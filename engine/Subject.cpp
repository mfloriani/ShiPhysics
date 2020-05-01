#include "Subject.h"

namespace ecs
{
	void Subject::Register(Observer* observer)
	{
		m_observer.push_back(observer);
	}

	void Subject::Unregister(Observer* observer)
	{
		m_observer.erase();
	}
}