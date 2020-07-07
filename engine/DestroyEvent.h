#ifndef __DESTROY_EVENT_H__
#define __DESTROY_EVENT_H__

#include "Event.h"

namespace ecs
{
	struct DestroyEvent : public Event
	{
		DestroyEvent(uint32_t id) : 
			m_gameObjectId(id)
		{}

		uint32_t m_gameObjectId;
	};
}

#endif // !__DESTROY_EVENT_H__