#ifndef __PLAYER1_SCRIPT_H__
#define __PLAYER1_SCRIPT_H__

#include "../engine/Component.h"

namespace ecs
{
	class RigidbodyComponent;
	class TransformComponent;
	struct CollisionEvent;
}

class CannonScript;
class MissileLauncherScript;
class FlareLauncherScript;

class Player1Script : public ecs::Component
{
public:
	Player1Script(){}
	virtual ~Player1Script() {}

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	
private:
	ecs::TransformComponent*	m_transform;
	ecs::RigidbodyComponent*	m_rigidbody;
	CannonScript*				m_cannon;
	MissileLauncherScript*		m_missileLauncher;
	FlareLauncherScript*		m_flareLauncher;
	float						m_rotationSpeed;
	float						m_thurstForce;

	inline void HandleInput(float dt);
	inline void HandleOffScreen();
};

#endif // !__PLAYER1_SCRIPT_H__