#include "AudioSystem.h"
#include <algorithm>
#include "Engine.h"
#include "AssetManager.h"
#include "MusicManager.h"
#include "SoundManager.h"

namespace ecs
{
	void AudioSystem::Update(float dt)
	{
		if (m_head == m_tail) return;

		auto sound = Engine::AssetMgr->GetSound(m_pending[m_head].m_id);
		SoundManager::SetVolume(sound, m_pending[m_head].m_volume);
		SoundManager::Play(sound);
		m_head = (m_head + 1) % MAX_AUDIO_PENDING;
	}

	void AudioSystem::PlaySound(std::string id, unsigned int volume)
	{
		if ((m_tail + 1) % MAX_AUDIO_PENDING == m_head) return;

		//merge duplicated sounds
		for (int i = m_head; i != m_tail; i = (i + 1) % MAX_AUDIO_PENDING)
		{
			if (m_pending[i].m_id == id)
			{
				m_pending[i].m_volume = std::max(volume, m_pending[i].m_volume);
				return;
			}
		}

		m_pending[m_tail].m_id = id;
		m_pending[m_tail].m_volume = volume;
		m_tail = (m_tail + 1) % MAX_AUDIO_PENDING;
	}

	void AudioSystem::PlayMusic(std::string id)
	{
		auto music = Engine::AssetMgr->GetMusic(id);
		MusicManager::SetVolume(MUSIC_VOLUME);
		MusicManager::Play(music);
		m_playingMusic = true;
	}

	void AudioSystem::ToggleMusic()
	{
		if (m_playingMusic)
		{
			Mix_PauseMusic();
		}
		else
		{
			Mix_ResumeMusic();
		}
		m_playingMusic = !m_playingMusic;
	}
}