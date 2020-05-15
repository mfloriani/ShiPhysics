#ifndef __FPS_SCRIPT_H__
#define __FPS_SCRIPT_H__

#include "../engine/Component.h"

namespace ecs
{
	class TextComponent;
}

class FPSScript : public ecs::Component
{
public:
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;

private:
	ecs::TextComponent* m_textComponent;
};

#endif // !__FPS_SCRIPT_H__