#ifndef __ASTEROID_SCRIPT_H__
#define __ASTEROID_SCRIPT_H__

#include "../engine/Component.h"

namespace ecs
{
	class TransformComponent;
}

class AsteroidScript : public ecs::Component
{
public:
	virtual void Init() override;	
	virtual void Update(float dt) override;
	virtual void Render() override;
private:
	ecs::TransformComponent* m_transform;
};

#endif // !__ASTEROID_SCRIPT_H__