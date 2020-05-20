#ifndef __AUDIO_SYSTEM_H__
#define __AUDIO_SYSTEM_H__

#include "System.h"
#include <string>
#include "Constants.h"
#include "PlaySoundEvent.h"

namespace ecs
{
	class AudioSystem: public System
	{
	public:
		AudioSystem(): 
			m_head(0),
			m_tail(0),
			m_playingMusic(false)
		{}

		virtual void Update(float dt) override;
		void PlaySound(std::string id, unsigned int volume);
		void PlayMusic(std::string id);
		void ToggleMusic();

	private:
		uint32_t		m_head;
		uint32_t		m_tail;
		PlaySoundEvent	m_pending[MAX_AUDIO_PENDING];
		bool			m_playingMusic;
	};
}

#endif // !__AUDIO_SYSTEM_H__