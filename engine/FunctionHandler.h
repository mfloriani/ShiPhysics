#ifndef __FUNCTION_HANDLER_H__
#define __FUNCTION_HANDLER_H__

#include "Event.h"

namespace ecs
{
	class FunctionHandler
	{
	public:
		void Invoke(Event* e)
		{
			Run(e);
		}
	private:
		virtual void Run(Event* e) = 0;
	};
}

#endif // !__FUNCTION_HANDLER_H__