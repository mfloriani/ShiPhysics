#ifndef __SPRITE_COMPONENT_H__
#define __SPRITE_COMPONENT_H__

#include "TextureManager.h"
#include "TransformComponent.h"
#include "Engine.h"

namespace ecs
{
	class SpriteComponent: public Component
	{
	public:
		SpriteComponent(std::string spriteId)
		{
			m_sprite = Engine::AssetMgr->GetTexture(spriteId);
		}

		~SpriteComponent()
		{

		}

		virtual void Init() override
		{
			m_transform = m_owner->GetComponent<TransformComponent>();
			SDL_QueryTexture(m_sprite, NULL, NULL, &m_dstrect.w, &m_dstrect.h);
		}

		virtual void Update(float dt) override 
		{
			m_dstrect.x = static_cast<int>(m_transform->m_position.x);
			m_dstrect.y = static_cast<int>(m_transform->m_position.y);
		}

		virtual void Render() override
		{	
			TextureManager::Render(m_sprite, &m_dstrect, glm::degrees(m_transform->m_angle));
		}

	private:
		SDL_Texture*		m_sprite;
		SDL_Rect			m_dstrect;
		TransformComponent*	m_transform;
	};
}

#endif