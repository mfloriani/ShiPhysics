#ifndef __FPS_SCRIPT_H__
#define __FPS_SCRIPT_H__

#include <SDL.h>
#include "../engine/Component.h"

class FPSScript : public ecs::Component
{
public:
	virtual void Init() override 
	{
		m_textComponent = m_owner->GetComponent<ecs::TextComponent>();
	}

	virtual void Update(float dt) override
	{
		//SDL_Log("%f", dt);
		auto fpsText = "FPS " + std::to_string(dt);
		m_textComponent->SetText(fpsText);
	}

	virtual void Render() override {}

private:
	ecs::TextComponent* m_textComponent;
};

#endif // !__FPS_SCRIPT_H__