#ifndef __HEALTH_SCRIPT_H__
#define __HEALTH_SCRIPT_H__

#include "../engine/Component.h"

namespace ecs
{
	struct CollisionEvent;
}

class HealthScript : public ecs::Component
{
public:
	HealthScript(int health) : m_health(health) {}
	~HealthScript();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;

	void OnCollisionEvent(ecs::CollisionEvent* e);

private:
	int m_health;
};

#endif // !__HEALTH_SCRIPT_H__