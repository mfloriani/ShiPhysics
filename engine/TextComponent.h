#ifndef __TEXT_COMPONENT_H__
#define __TEXT_COMPONENT_H__

#include <SDL_ttf.h>
#include <string>
#include "Component.h"

namespace ecs
{
	class TransformComponent;

	class TextComponent: public Component
	{
	public:
		TextComponent(std::string text, std::string fontFamily, SDL_Color color);
		~TextComponent();

		void SetText(std::string);
		void SetFontFamily(std::string fontFamily);

		virtual void Init() override;
		virtual void Update(float dt) override;
		virtual void Render() override;

	private:
		SDL_Texture*		m_texture;
		std::string			m_text;
		SDL_Color			m_color;
		std::string			m_fontFamily;
		TransformComponent* m_transform;
		SDL_Rect			m_position;
	};
}

#endif // !__TEXT_COMPONENT_H__