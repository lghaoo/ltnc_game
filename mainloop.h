#ifndef MAINLOOP_H_
#define MAINLOOP_H_

#include "Common.h"
#include "Tile.h"
#include "BaseObject.h"
#include "utils.h"
#include "play.h"
#include "background.h"
#include "menu.h"

class Mainloop
{
    private:
      Button *play_, *pause_, *quit_, *replay_ ,*level1_, *level2_, *level3_, *level4_,*level5_, *next_ ;
      TextObject *title , *you_win, *you_lose;
      Background back_ground;
      Play car;
      Map map, level1, level2, level3, level4, level5;
      SDL_Rect screen;
    
      BaseObject bg_start;
      GameState game_state;
      SDL_Rect bg_start_rect;

    public:
      Mainloop();
      void render_game();
      void handle_event(SDL_Event event);
      GameState get_game_state();
      void update_game_state(GameState new_state);


};


#endif