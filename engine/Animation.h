#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL.h>
#include <vector>

namespace ecs
{
	struct Animation
	{
		Animation(
			std::vector<SDL_Rect> clips,
			uint32_t frameRate,
			bool loop) :
			m_clips(clips),
			m_frameRate(frameRate),
			m_loop(loop)
		{}

		std::vector<SDL_Rect>	m_clips;
		unsigned int			m_frameRate;
		bool					m_loop;
	};
}

#endif // !__ANIMATION_H__