#ifndef __COLLISION_SYSTEM_H__
#define __COLLISION_SYSTEM_H__

#include <SDL.h>

//TODO: make this a system class in the future

namespace ecs
{
	inline bool CheckBoxCollision(SDL_Rect* boxL, SDL_Rect* boxR)
	{
		return SDL_HasIntersection(boxL, boxR);
	}
}

#endif // !__COLLISION_SYSTEM_H__