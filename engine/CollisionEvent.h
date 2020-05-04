#ifndef __COLLISION_EVENT_H__
#define __COLLISION_EVENT_H__

#include "Event.h"

namespace ecs
{
	class GameObject;

	class CollisionEvent : public Event
	{
	public:
		CollisionEvent(GameObject* goLeft, GameObject* goRight) :
			m_gameObjectLeft(goLeft),
			m_gameObjectRight(goRight),
			Event(EventType::COLLISION)
		{}

		~CollisionEvent() {}

	private:
		GameObject* m_gameObjectLeft;
		GameObject* m_gameObjectRight;
	};
}

#endif // !__COLLISION_EVENT_H__