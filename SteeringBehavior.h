#ifndef __STEERING_BEHAVIOR_H__
#define __STEERING_BEHAVIOR_H__

#include "Vector2D.h"
#include "GameObject.h"

class SteeringBehavior {

public:
	SteeringBehavior(GameObject* agent);
	~SteeringBehavior() {};

	math::Vector2D Seek(math::Vector2D targetPos);
	math::Vector2D Pursuit();
	math::Vector2D Flee();

	void SetTarget(GameObject* target) { m_target = target; }

private:
	GameObject* m_agent;
	GameObject* m_target;
};

#endif // !__STEERING_BEHAVIOR__

