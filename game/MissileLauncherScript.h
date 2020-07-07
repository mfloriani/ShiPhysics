#ifndef __MISSILE_LAUNCHER_SCRIPT_H__
#define __MISSILE_LAUNCHER_SCRIPT_H__

#include "../engine/Component.h"

namespace ecs
{
	class TransformComponent;
}

class MissileLauncherScript : public ecs::Component
{
public:
	MissileLauncherScript(float rateOfFire) :
		m_rateOfFire(rateOfFire),
		m_cooldown(0)
	{}

	virtual ~MissileLauncherScript() {}
	
	virtual void Init() override;	
	virtual void Update(float dt) override;
	virtual void Render() override;
	void Launch();

private:
	ecs::TransformComponent*	m_transform;
	float						m_rateOfFire; //TODO: create weapon class to handle cooldown
	float						m_cooldown;
};

#endif // !__MISSILE_LAUNCHER_SCRIPT_H__