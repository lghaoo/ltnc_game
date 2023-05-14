#ifndef SOUND_H_
#define SOUND_H_
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>


using namespace std;

extern Mix_Music* sound_background;
extern Mix_Music* start_game;


extern Mix_Chunk* button_select_sound;


bool LoadMusic();
void CloseMusic();

#endif // !SDL_MIXER_FUNCTION_H
