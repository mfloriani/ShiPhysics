#include "BoxColliderComponent.h"
#include "TransformComponent.h"
#include "Engine.h"

namespace ecs
{
	void BoxColliderComponent::Init() 
	{
		m_transform = m_owner->GetComponent<TransformComponent>();
		m_collider.x = static_cast<int>(m_transform->m_position.x) + m_offsetX;
		m_collider.y = static_cast<int>(m_transform->m_position.y) + m_offsetY;
		m_collider.w = m_width;
		m_collider.h = m_height;
	}

	void BoxColliderComponent::Update(float dt)
	{
		m_collider.x = static_cast<int>(m_transform->m_position.x) + m_offsetX;
		m_collider.y = static_cast<int>(m_transform->m_position.y) + m_offsetY;
	}

	void BoxColliderComponent::Render()
	{
		SDL_SetRenderDrawColor(Engine::Renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(Engine::Renderer, &m_collider);
	}

	const SDL_Rect& BoxColliderComponent::GetCollider() const
	{
		return m_collider;
	}
}