#ifndef __SPRITE_COMPONENT_H__
#define __SPRITE_COMPONENT_H__

#include <string>
#include <SDL.h>
#include "Component.h"

namespace ecs
{
	class TransformComponent;

	class SpriteComponent: public Component
	{
	public:
		SpriteComponent(std::string spriteId);
		~SpriteComponent();

		virtual void Init() override;

		virtual void Update(float dt) override;

		virtual void Render() override;

		friend class AnimationComponent;

	private:
		SDL_Texture*		m_sprite;
		SDL_Rect			m_srcrect;
		SDL_Rect			m_dstrect;
		TransformComponent*	m_transform;
	};
}

#endif