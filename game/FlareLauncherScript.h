#ifndef __FLARE_LAUNCHER_SCRIPT_H__
#define __FLARE_LAUNCHER_SCRIPT_H__

#include "../engine/Component.h"

namespace ecs
{
	class TransformComponent;
}

class FlareLauncherScript : public ecs::Component
{
public:
	FlareLauncherScript(float rateOfFire) :
		m_rateOfFire(rateOfFire),
		m_cooldown(0)
	{}

	virtual ~FlareLauncherScript() {}

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	void Launch();

private:
	ecs::TransformComponent*	m_transform;
	float						m_rateOfFire; //TODO: create weapon class to handle cooldown
	float						m_cooldown;
};

#endif // !__FLARE_LAUNCHER_SCRIPT_H__