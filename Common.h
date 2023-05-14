#ifndef COMMON_H_
#define COMMON_H_
#include <SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 682;
const int SCREEN_HEIGHT = 682;


const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};

enum GameState {
    STARTING_SCREEN,
    INSTRUCTION,
    PLAYING_THE_GAME,
    QUITTING_THE_GAME,
    WIN,
    GAME_OVER,
    NEXT,
    
    RESTARTING,
    CHOOSING_LEVEL
};






const static char WINDOW_TITLE[] = "Shot path";

#endif
