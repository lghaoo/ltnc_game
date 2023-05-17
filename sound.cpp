#include "sound.h"
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

using namespace std;

Mix_Music* sound_background = NULL;
Mix_Music* start_game = NULL;
Mix_Music* game_win = NULL;
Mix_Chunk* button_select_sound = NULL;


bool LoadMusic()
{
	bool res = true;
   start_game = Mix_LoadMUS("sound/start.mp3");
    if (start_game == NULL)
    {
        res = false;

    }
    button_select_sound =Mix_LoadWAV("sound/meomeo.mp3");
    if (button_select_sound == NULL)
    {
        res = false;
    }
    game_win = Mix_LoadMUS("sound/cat.mp3");
    if( game_win == NULL)
    {
        res = false;
    }
    return res;

}
void CloseMusic()
{
	
	Mix_FreeChunk(button_select_sound);
	
	button_select_sound = NULL;
	Mix_FreeMusic(start_game);
	start_game = NULL;
	Mix_Quit();
}
