#ifndef __EXPLOSION_SCRIPT_H__
#define __EXPLOSION_SCRIPT_H__

#include "../engine/Component.h"

namespace ecs
{
	class TransformComponent;
	struct DestroyEvent;
}

class ExplosionScript : public ecs::Component
{
public:
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;

	void ExplosionScript::OnDestroyEvent(ecs::DestroyEvent* e);

private:
	ecs::TransformComponent* m_transform;
};

#endif // !__EXPLOSION_SCRIPT_H__