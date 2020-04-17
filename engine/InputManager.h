#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include <SDL.h>
#include <vector>

namespace ecs
{
	class InputManager
	{
	public:
		void Update();
		const std::vector<SDL_Event>& GetEvents()const { return m_events; }

	private:
		std::vector<SDL_Event>	m_events;
	};
}

#endif // !__INPUT_MANAGER_H__