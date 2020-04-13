#ifndef __TEXT_COMPONENT_H__
#define __TEXT_COMPONENT_H__

#include <SDL_ttf.h>
#include <string>
#include "Engine.h"
#include "FontManager.h"

namespace ecs
{
	class TextComponent
	{
	public:
		TextComponent(SDL_Rect position, std::string text, std::string fontFamily, SDL_Color color):
			m_position(position),
			m_text(text),
			m_color(color),
			m_fontFamily(fontFamily)
		{
			SetText(text);
		}

		~TextComponent()
		{
			SDL_DestroyTexture(m_texture);
		}

		void SetText(std::string)
		{
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

		void SetFontFamily(std::string fontFamily)
		{
			if (!Engine::AssetMgr->HasFont(fontFamily))
			{
				SDL_Log("Invalid font %s", fontFamily);
				return;
			}
			m_fontFamily = fontFamily;
		}

		void Render()
		{
			FontManager::Render(m_texture, m_position);
		}

	private:
		SDL_Texture*	m_texture;
		std::string		m_text;
		SDL_Color		m_color;
		SDL_Rect		m_position;
		std::string		m_fontFamily;


	};
}

#endif // !__TEXT_COMPONENT_H__



