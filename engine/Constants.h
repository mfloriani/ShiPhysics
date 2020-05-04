#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <string>

const int WINDOW_WIDTH{ 1024 };
const int WINDOW_HEIGHT{ 768 };

const int FPS{ 60 };
const float FRAME_LENGTH{ 1000 / FPS };

const int SHIP_SIZE{ 32 };

const std::string UI_FONT_FAMILY = "arial";

const int UI_ARMOR_P1_X = 0;
const int UI_ARMOR_P1_Y = 0;

const int UI_LIFE_P1_X = UI_ARMOR_P1_X;
const int UI_LIFE_P1_Y = UI_ARMOR_P1_Y + 32;

const int UI_ARMOR_P2_X = 0;
const int UI_ARMOR_P2_Y = WINDOW_HEIGHT - 64;

const int UI_LIFE_P2_X = 0;
const int UI_LIFE_P2_Y = UI_ARMOR_P2_Y + 32;

const int UI_GAMEOVER_X = WINDOW_WIDTH/2;
const int UI_GAMEOVER_Y = WINDOW_HEIGHT/2;

const int SOUND_VOLUME = 20;
const int MUSIC_VOLUME = 20;

#endif