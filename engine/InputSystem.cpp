#include "InputSystem.h"

namespace ecs
{
	void InputSystem::Update(float dt)
	{
		m_events.clear();
		SDL_Event event;
		//while (SDL_PollEvent(&event) != 0)
		//{
		SDL_PollEvent(&event);
		m_events.push_back(event);
		//}
	}
}