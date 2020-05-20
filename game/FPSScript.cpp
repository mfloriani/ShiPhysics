#include "FPSScript.h"
#include <string>
#include "../engine/Engine.h"
#include "../engine/GameObjectManager.h"
#include "../engine/TextComponent.h"
#include "../engine/GameObject.h"

void FPSScript::Init()
{
	m_textComponent = ecs::Engine::GameObjectMgr->Get(m_owner)->GetComponent<ecs::TextComponent>();
}

void FPSScript::Update(float dt)
{
	//SDL_Log("%f", dt);
	auto fpsText = "FPS " + std::to_string(dt);
	m_textComponent->SetText(fpsText);
}

void FPSScript::Render() {}