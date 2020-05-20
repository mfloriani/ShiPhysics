#include "Player1Script.h"
#include "../lib/glm/gtx/rotate_vector.hpp"
#include "../engine/GameObject.h"
#include "../engine/TransformComponent.h"
#include "../engine/RigidbodyComponent.h"
#include "../engine/InputSystem.h"
#include "../engine/Engine.h"
#include "../engine/EventSystem.h"
#include "../engine/CollisionEvent.h"
#include "../engine/GameObjectManager.h"
#include "CannonScript.h"
#include "MissileLauncherScript.h"
#include "FlareLauncherScript.h"

void Player1Script::Init()
{
	m_transform = ecs::Engine::GameObjectMgr->Get(m_owner)->GetComponent<ecs::TransformComponent>();
	m_rigidbody = ecs::Engine::GameObjectMgr->Get(m_owner)->GetComponent<ecs::RigidbodyComponent>();
	m_cannon = ecs::Engine::GameObjectMgr->Get(m_owner)->GetComponent<CannonScript>();
	m_missileLauncher = ecs::Engine::GameObjectMgr->Get(m_owner)->GetComponent<MissileLauncherScript>();
	m_flareLauncher = ecs::Engine::GameObjectMgr->Get(m_owner)->GetComponent<FlareLauncherScript>();

	//TODO: load fixed values from config file
	m_thurstForce = 300.f;
	m_rotationSpeed = 2.f;
};

void Player1Script::Update(float dt)
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

void Player1Script::Render() {}