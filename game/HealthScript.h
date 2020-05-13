#ifndef __HEALTH_SCRIPT_H__
#define __HEALTH_SCRIPT_H__

#include "../engine/Component.h"

class HealthScript : public ecs::Component
{
public:
	HealthScript(int health) : m_health(health) {}
	~HealthScript(){}

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;

private:
	int m_health;
};

#endif // !__HEALTH_SCRIPT_H__