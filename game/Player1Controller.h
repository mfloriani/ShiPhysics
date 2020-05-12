#ifndef __PLAYER_CONTROLLER_H__
#define __PLAYER_CONTROLLER_H__

#include "../engine/Engine.h"
#include "../engine/InputSystem.h"
#include "../engine/Component.h"
#include "../engine/TransformComponent.h"
#include "../lib/glm/gtx/rotate_vector.hpp"
#include "Cannon.h"
#include "MissileLauncher.h"
#include "FlareLauncher.h"

class Player1Controller : public ecs::Component
{
public:
	virtual ~Player1Controller() {}

	virtual void Init() override
	{
		m_transform = m_owner->GetComponent<ecs::TransformComponent>();
		m_rigidbody = m_owner->GetComponent<ecs::RigidbodyComponent>();
		m_cannon = m_owner->GetComponent<Cannon>();
		m_missileLauncher = m_owner->GetComponent<MissileLauncher>();
		m_flareLauncher = m_owner->GetComponent<FlareLauncher>();

		//TODO: load from config file
		m_thurstForce = 300.f;
		m_rotationSpeed = 10.f;
	};

	virtual void Update(float dt) override
	{
		auto events = ecs::Engine::InputSys->GetEvents();
		for (auto event : events)
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_RIGHT:
				{
					m_transform->m_angle += m_rotationSpeed * dt;
					break;
				}
				case SDLK_LEFT:
				{
					m_transform->m_angle -= m_rotationSpeed * dt;
					break;
				}
				case SDLK_UP:
				{
					glm::vec2 force = glm::rotate(glm::vec2(1, 0) * m_thurstForce, m_transform->m_angle);
					m_rigidbody->AddForce(force);
					break;
				}
				case SDLK_RSHIFT:
				{
					if (m_cannon)
					{
						m_cannon->Shoot();
					}

					break;
				}
				case SDLK_RCTRL:
				{
					if (m_missileLauncher)
					{
						m_missileLauncher->Launch();
					}
					break;
				}
				case SDLK_BACKSPACE:
				{
					if (m_flareLauncher)
					{
						m_flareLauncher->Launch();
					}
					break;
				}
				}
			}
		}

		//SDL_Log("x=%f y=%f", m_transform->m_position.x, m_transform->m_position.y);
	};

	virtual void Render() override {};

private:
	ecs::TransformComponent*	m_transform;
	ecs::RigidbodyComponent*	m_rigidbody;
	Cannon*						m_cannon;
	MissileLauncher*			m_missileLauncher;
	FlareLauncher*				m_flareLauncher;

	float						m_rotationSpeed;
	float						m_thurstForce;
	
};

#endif // !__PLAYER_CONTROLLER_H__