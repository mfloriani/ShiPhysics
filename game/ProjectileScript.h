#ifndef __PROJECTILE_SCRIPT_H__
#define __PROJECTILE_SCRIPT_H__

#include "../engine/Component.h"

namespace ecs
{
	struct CollisionEvent;
}

class ProjectileScript : public ecs::Component
{
public:
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;

	void ProjectileScript::OnCollisionEvent(ecs::CollisionEvent* e);
};

#endif // !__PROJECTILE_SCRIPT_H__