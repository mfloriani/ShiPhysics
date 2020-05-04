#include "InputSystem.h"

namespace ecs
{
	void InputSystem::Update()
	{
		m_events.clear();
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			m_events.push_back(event);
		}
	}
}