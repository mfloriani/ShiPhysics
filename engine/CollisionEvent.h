#ifndef __COLLISION_EVENT_H__
#define __COLLISION_EVENT_H__

#include "Event.h"

namespace ecs
{
	class GameObject;

	struct CollisionEvent : public Event
	{
		CollisionEvent(GameObject* left, GameObject* right) :
			m_gameObjectLeft(left),
			m_gameObjectRight(right)
		{}

		~CollisionEvent() {}

		GameObject* m_gameObjectLeft;
		GameObject* m_gameObjectRight;
	};
}

#endif // !__COLLISION_EVENT_H__