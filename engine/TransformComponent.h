#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__

#include "../lib/glm/glm.hpp"
#include "Component.h"

namespace ecs
{
	class TransformComponent : public Component
	{
	public:
		TransformComponent();
		TransformComponent(glm::vec2 position, glm::vec2 direction, float angle);
		~TransformComponent();

		virtual void Init() override;
		virtual void Update(float dt) override;
		virtual void Render() override;

		glm::vec2	m_position;
		glm::vec2	m_direction;
		float		m_angle;
	};
}

#endif // !__TRANSFORM_COMPONENT_H__