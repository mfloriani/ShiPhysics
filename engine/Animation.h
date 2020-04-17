#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL.h"


class Animation
{
public:
	Animation(SDL_Texture* spriteSheet, int frames, SDL_Rect frameClips[]);
	~Animation();
	bool Draw(int x, int y);
	

private:
	SDL_Texture* m_spriteSheet;
	int m_frames;
	int m_currentFrame;
	int m_currentFrameTime;
	SDL_Rect m_frameClips[10];
	
};

#endif
