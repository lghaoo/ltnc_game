#ifndef MAINLOOP_H_
#define MAINLOOP_H_

#include "Common.h"
#include "Tile.h"
#include "BaseObject.h"
#include "utils.h"
#include "play.h"
#include "background.h"
#include "menu.h"
#include "sound.h"

class Mainloop
{
    private:
      Button *play_, *quit_,*level1_, *level2_, *level3_, *level4_,*level5_ ,*instructions , *replay , *menu ,*play_next , *exit;
      TextObject  *quit_intro;
      Background back_ground;
      Play car;
      Map map, level1, level2, level3, level4, level5;
      SDL_Rect screen;
    
      BaseObject bg_start;
      BaseObject instruc;
      BaseObject game_over;
      BaseObject level_up;
      

      GameState game_state;

      int tmp;

      SDL_Rect instruc_rect;
      SDL_Rect bg_start_rect;
      SDL_Rect game_over_rect;
      SDL_Rect level_up_rect;
      

     

    public:
      Mainloop();
      void render_game();
      void handle_event(SDL_Event event);
      GameState get_game_state();
      void update_game_state(GameState new_state);


};


#endif