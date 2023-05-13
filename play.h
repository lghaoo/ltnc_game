#ifndef PLAY_H_
#define PLAY_H_

#include "common.h"
#include "BaseObject.h"
#include "Tile.h"


class Play
{
   
    public:
      Play();
      ~Play();
      enum WaikType
      {
     
        WAIK_RIGHT,
        WAIK_LEFT,
        WAIK_UP,
        WAIK_DOWN,
      };

      static const int PLAYER_WIDTH = 60;
      static const int PLAYER_HEIGHT = 60;
      static const int PLAYER_SPEED = 5;
     
    void init();

    void handleEvent(SDL_Event& e);

    void move(vector<Tile*> tiles, Map level);

    
    void render(SDL_Rect &des);
    
  
    

    bool is_game_over(SDL_Rect camera);

    bool win(Map level);

    int pos_start(vector<Tile*> tiles, Map level);

    int getPosX();
    int getPosY();
   private:
   
    SDL_Rect mBox;

    SDL_Rect current_clip;
   
    WaikType player_state;
    
    float x_val, y_val;
  
    BaseObject mTexture;
    
    SDL_RendererFlip player_flip;
    
    
    
};

#endif 