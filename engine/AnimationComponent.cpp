#include "AnimationComponent.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Engine.h"
#include "GameObjectManager.h"
#include "AssetManager.h"
#include "Animation.h"

namespace ecs
{
	AnimationComponent::AnimationComponent(std::string id) :
		m_frameCount(0),
		m_ended(false)
	{
		m_animation = Engine::AssetMgr->GetAnimation(id);
	}

	AnimationComponent::~AnimationComponent()
	{
	}

	void AnimationComponent::Init()
	{
		m_frameCount = m_animation->m_clips.size();
		m_spriteComponent = Engine::GameObjectMgr->Get(m_owner)->GetComponent<SpriteComponent>();
		m_spriteComponent->m_srcrect = m_animation->m_clips[0];
		m_spriteComponent->m_dstrect.w = m_animation->m_clips[0].w;
		m_spriteComponent->m_dstrect.h = m_animation->m_clips[0].h;
	}

	void AnimationComponent::Update(float dt)
	{
		if (m_ended) return;
		
		int frame = static_cast<int>((SDL_GetTicks() / m_animation->m_frameRate) % m_frameCount);

		m_spriteComponent->m_srcrect = m_animation->m_clips[frame];
		m_spriteComponent->m_dstrect.w = m_animation->m_clips[frame].w;
		m_spriteComponent->m_dstrect.h = m_animation->m_clips[frame].h;

		//TODO: implement state machine
		//		send event informing that animation has ended
		if (!m_animation->m_loop && frame == (m_frameCount-1)) m_ended = true;
	}

	void AnimationComponent::Render()
	{

	}
}