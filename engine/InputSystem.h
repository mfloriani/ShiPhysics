#ifndef __INPUT_SYSTEM_H__
#define __INPUT_SYSTEM_H__

#include <SDL.h>
#include <vector>
#include "System.h"

namespace ecs
{
	class InputSystem : public System
	{
	public:
		virtual void Update(float dt) override;
		const std::vector<SDL_Event>& GetEvents()const { return m_events; }

	private:
		std::vector<SDL_Event>	m_events;
	};
}

#endif // !__INPUT_MANAGER_H__