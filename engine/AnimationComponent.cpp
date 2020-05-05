#include "AnimationComponent.h"
#include "GameObject.h"
#include "SpriteComponent.h"

namespace ecs
{
	AnimationComponent::AnimationComponent(FrameClips clips, bool loop) :
		m_frameClips(clips),
		m_frameCount(clips.size()),
		m_loop(loop),
		m_ended(false)
	{
		
	}

	AnimationComponent::~AnimationComponent()
	{
	}

	void AnimationComponent::Init()
	{
		m_spriteComponent = m_owner->GetComponent<SpriteComponent>();
	}

	void AnimationComponent::Update(float dt)
	{
		if (m_ended) return;
		//if (++m_currentFrameTime >= 12)//keep twelve frames the same frame
		//{
		//	++m_currentFrame;
		//	if (m_currentFrame >= m_frames)
		//	{
		//		m_currentFrame = 0;
		//		return true;
		//	}
		//}
		//SDL_Rect clip = m_frameClips[m_currentFrame];
		//SDL_Rect dstRect{ x,  y, 60, 59 }; //remove fixed size
		//ecs::TextureManager::Render(m_spriteSheet, &clip, &dstRect);

		int frame = static_cast<int>((SDL_GetTicks() / 200) % m_frameCount);

		m_spriteComponent->m_srcrect = m_frameClips[frame];
		m_spriteComponent->m_dstrect.w = m_frameClips[frame].w;
		m_spriteComponent->m_dstrect.h = m_frameClips[frame].h;

		//TODO: implement state machine
		//		send event informing that animation has ended
		if (!m_loop && frame == (m_frameCount-1)) m_ended = true;
	}

	void AnimationComponent::Render()
	{

	}
}