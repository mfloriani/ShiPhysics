#ifndef __COLLISION_SYSTEM_H__
#define __COLLISION_SYSTEM_H__

#include <SDL.h>
#include "TransformComponent.h"
#include "Engine.h"

//TODO: make this a system class in the future

namespace ecs
{
	inline bool CheckBoxCollision(SDL_Rect* boxL, SDL_Rect* boxR)
	{
		return SDL_HasIntersection(boxL, boxR);
	}

	//TODO: move to a Camera class
	inline bool IsOffScreen(TransformComponent* transform)
	{
		if (transform->m_position.x < 0.f || transform->m_position.x > Engine::Camera->w ||
			transform->m_position.y < 0.f || transform->m_position.y > Engine::Camera->h)
		{
			return true;
		}
		return false;
	}
}

#endif // !__COLLISION_SYSTEM_H__