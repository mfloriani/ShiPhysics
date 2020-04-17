#ifndef __BOX_COLLIDER_COMPONENT_H__
#define __BOX_COLLIDER_COMPONENT_H__

#include <SDL.h>
#include "Component.h"
#include "TransformComponent.h"

namespace ecs
{
	class BoxColliderComponent : public Component
	{
	public:
		BoxColliderComponent(int offsetX, int offsetY, int width, int height):
			m_offsetX(offsetX),
			m_offsetY(offsetY),
			m_width(width),
			m_height(height)
		{}

		~BoxColliderComponent() {}

		virtual void Init() override
		{
			m_transform = m_owner->GetComponent<TransformComponent>();
			m_collider.x = static_cast<int>(m_transform->m_position.x) + m_offsetX;
			m_collider.y = static_cast<int>(m_transform->m_position.y) + m_offsetY;
			m_collider.w = m_width;
			m_collider.h = m_height;
		}

		virtual void Update(float dt) override 
		{
			m_collider.x = static_cast<int>(m_transform->m_position.x) + m_offsetX;
			m_collider.y = static_cast<int>(m_transform->m_position.y) + m_offsetY;
		}

		virtual void Render() override 
		{
			SDL_SetRenderDrawColor(Engine::Renderer, 255, 0, 0, 255);
			SDL_RenderDrawRect(Engine::Renderer, &m_collider);
		}

	private:
		SDL_Rect			m_collider;
		TransformComponent* m_transform;
		int					m_offsetX;
		int					m_offsetY;
		int					m_width;
		int					m_height;
	};
}

#endif // !__BOX_COLLIDER_COMPONENT_H__