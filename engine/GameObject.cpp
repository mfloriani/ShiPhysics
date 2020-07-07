#include "GameObject.h"
#include "Component.h"

namespace ecs
{
	GameObject::~GameObject()
	{
		Free();
	}

	void GameObject::Update(float dt)
	{
		for (auto c : m_components)
		{
			c->Update(dt);
		}
	}

	void GameObject::Render()
	{
		for (auto c : m_components)
		{
			c->Render();
		}
	}

	void GameObject::Free()
	{
		for (auto c : m_components)
		{
			delete c;
		}
		m_components.clear();
	}
}