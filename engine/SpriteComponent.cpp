#include "SpriteComponent.h"
#include "Engine.h"
#include "AssetManager.h"
#include "TransformComponent.h"
#include "TextureManager.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "GameObjectManager.h"

namespace ecs
{
	SpriteComponent::SpriteComponent(std::string spriteId)		
	{
		m_sprite = Engine::AssetMgr->GetTexture(spriteId);
	}

	SpriteComponent::~SpriteComponent()
	{

	}

	void SpriteComponent::Init()
	{
		m_transform = Engine::GameObjectMgr->Get(m_owner)->GetComponent<TransformComponent>();
		SDL_QueryTexture(m_sprite, NULL, NULL, &m_dstrect.w, &m_dstrect.h);
		m_srcrect = { 0, 0, m_dstrect.w , m_dstrect.h };
	}

	void SpriteComponent::Update(float dt)
	{
		m_dstrect.x = static_cast<int>(m_transform->m_position.x);
		m_dstrect.y = static_cast<int>(m_transform->m_position.y);
	}

	void SpriteComponent::Render()
	{
		TextureManager::Render(m_sprite, &m_srcrect, &m_dstrect, glm::degrees(m_transform->m_angle));
	}
}