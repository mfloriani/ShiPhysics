#ifndef __COLLISION_OBSERVER_H__
#define __COLLISION_OBSERVER_H__

#include "Observer.h"

namespace ecs
{
	class CollisionObserver : public Observer
	{
	public:
		virtual void OnNotify(Event* event) override;
	};
}

#endif // !__COLLISION_OBSERVER_H__