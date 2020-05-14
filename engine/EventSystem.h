#ifndef __EVENT_SYSTEM_H__
#define __EVENT_SYSTEM_H__

#include "MemberFunctionHandler.h"
#include <vector>
#include <map>
#include <typeindex>

namespace ecs
{
	typedef std::vector<FunctionHandler*> Handlers;

	class EventSystem
	{
	public:
		template<typename EventType>
		void Publish(EventType* e)
		{
			Handlers* handlers = m_subscribers[typeid(EventType)];
			if (!handlers) return;

			for (auto handler : *handlers)
			{
				if (!handler) continue;
				handler->Invoke(e);
			}
		}

		template<class T, class EventType>
		void Subscribe(T* instance, void (T::*memberFunction)(EventType*))
		{
			Handlers* handlers = m_subscribers[typeid(EventType)];

			if (!handlers)
			{
				handlers = new Handlers;
				m_subscribers[typeid(EventType)] = handlers;
			}

			handlers->push_back(new MemberFunctionHandler<T, EventType>(instance, memberFunction));
		}

		//TODO: delete handlers

	private:
		std::map<std::type_index, Handlers*> m_subscribers;
	};
}

#endif // !__EVENT_SYSTEM_H__