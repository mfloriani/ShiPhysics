#ifndef __EVENT_H__
#define __EVENT_H__

namespace ecs
{
	enum EventType
	{
		COLLISION = 1
	};

	class Event
	{
	public:
		Event(EventType type) : m_type(type) {}
		virtual ~Event(){}
	protected:
		EventType m_type;
	};
}

#endif // !__EVENT_H__