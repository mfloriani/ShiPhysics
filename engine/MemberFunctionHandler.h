#ifndef __MEMBER_FUNCTION_HANDLER_H__
#define __MEMBER_FUNCTION_HANDLER_H__

#include "FunctionHandler.h"

namespace ecs
{
	template<class T, class EventType>
	class MemberFunctionHandler : public FunctionHandler
	{
	public:
		typedef void (T::*MemberFunction)(EventType*);

		MemberFunctionHandler(T* instance, MemberFunction memberFunction):
			m_instance(instance),
			m_memberFunction(memberFunction)
		{}

		virtual void Run(Event* e) override
		{
			(m_instance->*m_memberFunction)(static_cast<EventType*>(e));
		}

	private:
		T*				m_instance;
		MemberFunction	m_memberFunction;
	};
}

#endif // !__MEMBER_FUNCTION_HANDLER_H__