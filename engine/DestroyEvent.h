#ifndef __DESTROY_EVENT_H__
#define __DESTROY_EVENT_H__

#include "Event.h"

namespace ecs
{
	class GameObject;

	struct DestroyEvent : public Event
	{
		DestroyEvent(GameObject* go) : 
			m_gameObject(go)
		{}

		GameObject* m_gameObject;
	};
}

#endif // !__DESTROY_EVENT_H__