#include "TextComponent.h"
#include "Engine.h"
#include "FontManager.h"
#include "AssetManager.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace ecs
{
	TextComponent::TextComponent(
		std::string text,
		std::string fontFamily,
		SDL_Color color
	) :
		m_text(text),
		m_color(color),
		m_fontFamily(fontFamily)
	{

	}

	TextComponent::~TextComponent()
	{
		SDL_DestroyTexture(m_texture);
	}

	void TextComponent::SetText(std::string text)
	{
		m_text = text;
		if (m_texture)
		{
			SDL_DestroyTexture(m_texture);
		}
		TTF_Font* font = Engine::AssetMgr->GetFont(m_fontFamily);
		if (!font)
		{
			SDL_Log("Failed to load font %s", m_fontFamily);
			return;
		}
		SDL_Surface* surface = TTF_RenderText_Blended(font, m_text.c_str(), m_color);
		m_texture = SDL_CreateTextureFromSurface(Engine::Renderer, surface);
		SDL_FreeSurface(surface);
		SDL_QueryTexture(m_texture, NULL, NULL, &m_position.w, &m_position.h);
	}

	void TextComponent::SetFontFamily(std::string fontFamily)
	{
		if (!Engine::AssetMgr->HasFont(fontFamily))
		{
			SDL_Log("Invalid font %s", fontFamily);
			return;
		}
		m_fontFamily = fontFamily;
	}

	void TextComponent::Init()
	{
		m_transform = m_owner->GetComponent<TransformComponent>();
		m_position.x = static_cast<int>(m_transform->m_position.x);
		m_position.y = static_cast<int>(m_transform->m_position.y);

		SetText(m_text);
	}

	void TextComponent::Update(float dt)
	{
		//SetText(std::to_string(dt));
	}

	void TextComponent::Render()
	{
		FontManager::Render(m_texture, m_position);
	}
}