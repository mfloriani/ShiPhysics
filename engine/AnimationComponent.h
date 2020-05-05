#ifndef __ANIMATION_COMPONENT_H__
#define __ANIMATION_COMPONENT_H__

#include <vector>
#include "SDL.h"
#include "Component.h"

namespace ecs
{
	class SpriteComponent;

	typedef std::vector<SDL_Rect> FrameClips;

	class AnimationComponent : public Component
	{
	public:
		AnimationComponent(FrameClips clips, bool loop);
		~AnimationComponent();
		
		virtual void Init() override;
		virtual void Update(float dt) override;
		virtual void Render() override;


	private:
		FrameClips			m_frameClips;
		Uint32				m_frameCount;
		bool				m_loop;
		bool				m_ended;
		SpriteComponent*	m_spriteComponent;

	};
}
#endif