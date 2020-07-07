#include "TransformComponent.h"

namespace ecs
{
	TransformComponent::TransformComponent() :
		m_position(),
		m_direction(),
		m_angle(0.f)
	{}

	TransformComponent::TransformComponent(
		glm::vec2 position,
		glm::vec2 direction,
		float angle) :
		m_position(position),
		m_direction(direction),
		m_angle(angle)
	{}

	TransformComponent::~TransformComponent() {}

	void TransformComponent::Init() {}
	void TransformComponent::Update(float dt) {}
	void TransformComponent::Render() {}
}