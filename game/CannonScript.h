#ifndef __CANNON_H__
#define __CANNON_H__

#include "../engine/Component.h"

namespace ecs
{
	class TransformComponent;
}

class CannonScript : public ecs::Component
{
public:
	CannonScript(float rateOfFire) :
		m_rateOfFire(rateOfFire), 
		m_cooldown(0)
	{}
	
	virtual ~CannonScript() {}
	
	virtual void Init() override;
	virtual void Update(float dt) override;	
	virtual void Render() override;
	void Shoot();

private:
	ecs::TransformComponent*	m_transform;
	float						m_rateOfFire; //TODO: create weapon class to handle cooldown
	float						m_cooldown;
};

#endif // !__CANNON_H__