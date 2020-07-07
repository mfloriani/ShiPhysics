#ifndef __COLLISION_EVENT_H__
#define __COLLISION_EVENT_H__

#include "Event.h"

namespace ecs
{
	struct CollisionEvent : public Event
	{
		CollisionEvent(uint32_t left, uint32_t right) :
			m_leftGameObjectId(left),
			m_rightGameObjectId(right)
		{}

		~CollisionEvent() {}

		uint32_t m_leftGameObjectId;
		uint32_t m_rightGameObjectId;
	};
}

#endif // !__COLLISION_EVENT_H__