#ifndef __PLAY_SOUND_EVENT_H__
#define __PLAY_SOUND_EVENT_H__

#include "Event.h"

namespace ecs
{
	struct PlaySoundEvent : public Event
	{
		PlaySoundEvent(){}
		PlaySoundEvent(std::string id, unsigned int volume): 
			m_id(id), m_volume(volume)
		{}
		std::string m_id;
		unsigned int m_volume;
	};
}

#endif // !__PLAY_SOUND_EVENT_H__