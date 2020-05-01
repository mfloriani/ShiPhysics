#ifndef __BOX_COLLIDER_COMPONENT_H__
#define __BOX_COLLIDER_COMPONENT_H__

#include <SDL.h>
#include "Component.h"

namespace ecs
{
	class TransformComponent;

	class BoxColliderComponent : public Component
	{
	public:
		BoxColliderComponent(int offsetX, int offsetY, int width, int height) :
			m_offsetX(offsetX),
			m_offsetY(offsetY),
			m_width(width),
			m_height(height)
		{}

		~BoxColliderComponent() {}

		virtual void Init() override;

		virtual void Update(float dt) override;

		virtual void Render() override;

		const SDL_Rect& GetCollider() const;

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