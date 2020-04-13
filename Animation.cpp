#include "Animation.h"


Animation::Animation(Texture* spriteSheet, int frames, SDL_Rect frameClips[]):
m_spriteSheet(spriteSheet), m_frames(frames), m_currentFrame(0), m_currentFrameTime(0)
{
	for (int i = 0; i < frames; i++)
	{
		m_frameClips[i] = frameClips[i];
	}
}


Animation::~Animation()
{
}


bool Animation::Draw(float secs, int x, int y)
{
	if (++m_currentFrameTime >= 12)//keep twelve frames the same frame
	{
		++m_currentFrame;
		if (m_currentFrame >= m_frames)
		{
			m_currentFrame = 0;
			return true;
		}
	}
	SDL_Rect currentClip = m_frameClips[m_currentFrame];
	m_spriteSheet->Render(x, y, &currentClip);
}
