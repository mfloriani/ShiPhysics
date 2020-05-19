#ifndef __ANIMATION_COMPONENT_H__
#define __ANIMATION_COMPONENT_H__

#include <vector>
#include "SDL.h"
#include "Component.h"

namespace ecs
{
	class SpriteComponent;
	struct Animation;

	class AnimationComponent : public Component
	{
	public:
		AnimationComponent(std::string id);
		~AnimationComponent();
		
		virtual void Init() override;
		virtual void Update(float dt) override;
		virtual void Render() override;

	private:
		Animation*			m_animation;
		Uint32				m_frameCount;
		bool				m_ended;
		SpriteComponent*	m_spriteComponent;

	};
}
#endif