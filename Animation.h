#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL.h"

#include "Texture.h"


class Animation
{
public:
	Animation(Texture* spriteSheet, int frames, SDL_Rect frameClips[]);
	~Animation();
	bool Draw(float secs, int x, int y);
	

private:
	Texture* m_spriteSheet;
	int m_frames;
	int m_currentFrame;
	int m_currentFrameTime;
	SDL_Rect m_frameClips[10];
	
};

#endif
