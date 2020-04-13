#ifndef __SPRITE_COMPONENT_H__
#define __SPRITE_COMPONENT_H__

#include <SDL.h>
#include "TextureManager.h"

namespace ecs
{
	class SpriteComponent
	{
	public:
		SpriteComponent(SDL_Texture* sprite)
		{
			//SDL_Rect rect{ (int)m_position.x,  (int)m_position.y };
			//SDL_QueryTexture(m_sprite, NULL, NULL, &m_width, &m_height);
		}

		~SpriteComponent()
		{

		}

		void Render() const
		{
			//TextureManager::Render(sprite, )
		}

	private:
		SDL_Texture*	m_sprite;
		int				m_width;
		int				m_height;
	};
}

#endif