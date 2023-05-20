#include "mainloop.h"

using namespace std;


SDL_Event event;

int main(int argc, char** argv)
{
    initSDL(gWindow,gRenderer,SCREEN_WIDTH,SCREEN_HEIGHT,WINDOW_TITLE);
    
    Mainloop main_loop;
    Mix_PlayMusic(start_game,-1);
    while(main_loop.get_game_state() != QUITTING_THE_GAME)
    {
        main_loop.handle_event(event);
        SDL_RenderClear(gRenderer);
        main_loop.render_game();
        SDL_RenderPresent(gRenderer);
    }
    quitSDL(gWindow,gRenderer);
    return 0;
}
