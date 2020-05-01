#include "InputManager.h"

namespace ecs
{
	void InputManager::Update()
	{
		m_events.clear();
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			m_events.push_back(event);
		}
	}
}